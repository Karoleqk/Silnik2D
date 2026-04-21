#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"
#include "headers/LineSegment.h"

Engine::Engine(unsigned int w, unsigned int h) :
    width(w), height(h), window(sf::VideoMode({ w, h }), "Silnik 2D dino run"), primitiveRenderer(window, width, height),
    isDrawing(false), currentTool(PIXEL), currentClick(0) {

    // Pusta wstępna mapa
    this->map = std::vector<std::vector<int>>(14, std::vector<int>(17, 0));
    for (int x = 0; x < 17; x++) {
        map[12][x] = 1;
        map[13][x] = 1;
    }

    coinBmp.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sprites/coin.png");
    slimeBmp.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sprites/slime_green.png");

    if (coinBuffer.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sounds/coin.wav")) {
        coinSound.emplace(coinBuffer);
        coinSound->setVolume(70.f);
    }

    if (hurtBuffer.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sounds/hurt.wav")) {
        hurtSound.emplace(hurtBuffer);
        hurtSound->setVolume(70.f);
    }
};

void Engine::run(int fps) {
    window.setFramerateLimit(fps);
    player.setPosition({ 30, 400 });

    //std::vector<Point2D> quad = {
    //    Point2D(400, 300),
    //    Point2D(500, 400),
    //    Point2D(400, 500),
    //    Point2D(600, 400)
    //};
    //drawPolygon(quad, sf::Color::Yellow);

    // Obsluga playera z main.cpp

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Engine::resetGame() {
    score = 0;
    coinsCollected = 0;
    distanceTraveled = 0.0f;
    globalSpeed = 3.5f;
    mapOffsetX = 0;
    gameOver = false;
    entities.clear();

    this->map = std::vector<std::vector<int>>(14, std::vector<int>(17, 0));
    for (int x = 0; x < 17; x++) {
        map[10][x] = 1;
        map[11][x] = 1;
    }

    player.setPosition({ 150, 480 });
    player.setMap(this->map);
    background.setMap(this->map);

    std::cout << "restart" << std::endl;
}

// Funkcja do ogarniania eventów myszki/klawiatury, tutaj nic nie rysujemy, tylko rejestrujemy kliknięcia
void Engine::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                auto pos = sf::Mouse::getPosition(window);
                mouseClickPos = pos;
                isDrawing = true;
            }
        }

        if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (gameOver && keyPressed->code == sf::Keyboard::Key::Space) {
                resetGame();
            }

            switch (keyPressed->code) {
                case sf::Keyboard::Key::Num1:
                    currentTool = PIXEL;
                    break;

                case sf::Keyboard::Key::Num2:
                    currentTool = LINE;
                    break;

                case sf::Keyboard::Key::Num3:
                    currentTool = RECT;
                    break;

                case sf::Keyboard::Key::Num4:
                    currentTool = CIRCLE;
                    break;

                case sf::Keyboard::Key::Num5:
                    currentTool = FLOOD_FILL;
                    break;

                case sf::Keyboard::Key::Num6:
                    currentTool = BOUNDARY_FILL;
                    break;

                default:
                    break;
                }

            resetStartEnd();
        }
    }
}

void Engine::spawnEntity(int type, int x, int y) {
    GameEntity ent;
    ent.type = type;
    ent.position = { x, y };

    if (type == 0) {
        ent.sprite.setSheet(coinBmp);
        ent.sprite.mode = SINGLE;
        ent.sprite.setFrameSize(16, 16);
        ent.maxFrames = 12;
    }
    else {
        ent.sprite.setSheet(slimeBmp);
        ent.sprite.mode = SINGLE;
        ent.sprite.setFrameSize(24, 24);
        ent.maxFrames = 4;
    }
    entities.push_back(ent);
}

// Metoda do aktualizowania zmiennych
void Engine::update() {
    if (gameOver) return;

    globalSpeed += 0.002f;
    distanceTraveled += globalSpeed * 0.01f;

    player.update();
    player.animate(0.016f);
    player.position.x = 150;

    static float preciseOffsetX = 0;
    preciseOffsetX += globalSpeed;

    static int spawnCooldown = 0;

    while (preciseOffsetX >= 48.0f) {
        preciseOffsetX -= 48.0f;

        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[y].size() - 1; x++) {
                map[y][x] = map[y][x + 1];
            }
            map[y][map[y].size() - 1] = 0;
        }

        map[10][16] = 1;
        map[11][16] = 1;

        if (rand() % 8 == 0) map[6 + rand() % 2][16] = 2;

        background.setMap(map);
        player.setMap(map);

        if (spawnCooldown > 0) {
            spawnCooldown--;
        }
        else {
            if (rand() % 6 == 0) {
                spawnEntity(1, 850, 480);
                spawnCooldown = 4;
            }
            else if (rand() % 4 == 0) {
                spawnEntity(0, 850, 250 + rand() % 150);
                spawnCooldown = 2;
            }
        }
    }

    mapOffsetX = (int)preciseOffsetX;
    background.mapOffsetX = mapOffsetX;
    player.mapOffsetX = mapOffsetX;

    Rect pRect = player.getRect();
    int tileSize = 48;

    int left = (pRect.start.x + mapOffsetX + 8) / tileSize;
    int right = (pRect.start.x + pRect.width + mapOffsetX - 8) / tileSize;
    int top = (pRect.start.y + 4) / tileSize;
    int bottom = (pRect.start.y + pRect.height - 4) / tileSize;

    bool hitWall = false;
    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
            if (y >= 0 && y < map.size() && x >= 0 && x < map[0].size()) {
                if (map[y][x] == 1 || map[y][x] == 2) {
                    hitWall = true;
                }
            }
        }
    }

    if (hitWall) {
        gameOver = true;
        if (hurtSound) hurtSound->play();

        int finalScore = (int)distanceTraveled + (coinsCollected * 100);
        std::cout << "Zderzenie ze sciana\nDystans: " << (int)distanceTraveled << "\n Wynik: " << finalScore << "\n\n";
    }

    for (auto& ent : entities) {
        if (!ent.active) continue;

        ent.position.x -= globalSpeed;
        ent.sprite.setPosition(ent.position);

        ent.frameTimer++;
        if (ent.frameTimer > 6) {
            ent.frameTimer = 0;
            ent.currentFrame = (ent.currentFrame + 1) % ent.maxFrames;
            ent.sprite.setFrame(ent.currentFrame, 0);
        }

        Rect pRect = player.getRect();
        Rect eRect({ ent.position.x - 16, ent.position.y - 32 }, 32, 32);

        if (pRect.start.x < eRect.start.x + eRect.width &&
            pRect.start.x + pRect.width > eRect.start.x &&
            pRect.start.y < eRect.start.y + eRect.height &&
            pRect.start.y + pRect.height > eRect.start.y) {

            if (ent.type == 0) {
                coinsCollected++;
                ent.active = false;
                if (coinSound) coinSound->play();
            }
            else if (ent.type == 1) {
                gameOver = true;
                if (hurtSound) hurtSound->play();
                int finalScore = (int)distanceTraveled + (coinsCollected * 100);
                std::cout << "\nKoniec gry! \nWynik: " << finalScore << "\n\n";
            }
        }

        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                [](const GameEntity& e) { return e.position.x < -100 || !e.active; }),
            entities.end()
        );
    }

    //std::cout << "X: " << player.position.x << std::endl;
    //std::cout << "Y: " << player.position.y << std::endl;

    // TRANSLACJA

    //LineSegment line2({ 300, 300 }, { 400, 400 });
    //lines.push_back(line2);
    //line2.translate(300, 200);
    //lines.push_back(line2);


    // ----------------------------------------
    // Przykład działania rotate() na punkcie

    //Point2D base(420, 320);
    //for (float i = 0; i <= 360; i += 15) {
    //    Point2D point = base;
    //    point.rotate(i, middle);
    //    points.push_back(point);
    //}

    // ----------------------------------------


    // Przykład działania rotate() z animacją kręcenia się

    // ROTACJA

    //LineSegment base({ 450, 300 }, { 450, 350 });
    //angle += 0.5f;
    //lines.clear();
    //for (float i = 0; i <= 360; i += 30) {
    //    LineSegment l = base;
    //    l.rotate(i + angle, middle);
    //    lines.push_back(l);
    //}

    

    // SKALOWANIE

    //LineSegment base1({ 500, 275 }, { 500, 325 });
    //lines.push_back(base1);
    //for (float i = 2; i >= -2; i -= 0.5) {
    //    LineSegment line = base1;
    //    line.scale(i, middle);
    //    lines.push_back(line);
    //}
    


    // jesli isDrawing = true, to rysujemy piksel tam, gdzie kliknelismy myszka
    if (isDrawing) {
        if (currentTool == PIXEL)
            points.emplace_back(mouseClickPos.x, mouseClickPos.y);

        if (currentTool == CIRCLE)
            drawCircle({ mouseClickPos.x, mouseClickPos.y }, 50, sf::Color::Yellow);

        if (currentTool != PIXEL && currentTool != CIRCLE && currentTool != FLOOD_FILL && currentTool != BOUNDARY_FILL)
            drawShape();

        if (currentTool == FLOOD_FILL) {
            primitiveRenderer.floodFill({ mouseClickPos.x, mouseClickPos.y }, sf::Color::Red, sf::Color::Black);
        }

        if (currentTool == BOUNDARY_FILL) {
            primitiveRenderer.boundaryFill({ mouseClickPos.x, mouseClickPos.y }, sf::Color::Magenta, sf::Color::Yellow);
        }

        isDrawing = false;
    }
}

// Metoda do aktualizacji okna
// renderujemy za pomocą klasy PrimitiveRenderer
void Engine::render() {
    background.draw(primitiveRenderer);
    
    for (auto& ent : entities) {
        if (ent.active) ent.sprite.draw(primitiveRenderer);
    }

    player.draw(primitiveRenderer);

    //rectangles.clear();
    //Rect playerRect = player.getRect();
    //drawRect(playerRect.getStart(), playerRect.width, playerRect.height, sf::Color::Blue);


    //for (auto& line : lines) {
    //    line.draw(primitiveRenderer, sf::Color::Cyan);
    //}

    //for (auto& point : points) {
    //    point.draw(primitiveRenderer, sf::Color::Cyan);
    //}

    //for (auto& rect : rectangles) {
    //    rect.draw(primitiveRenderer, sf::Color::Cyan);
    //}

    primitiveRenderer.render();
}

// funkcja do wybierania punktow przy rysowaniu myszką
void Engine::drawShape() {
    if (currentClick == 0) {
        start.x = mouseClickPos.x;
        start.y = mouseClickPos.y;
    }
    else if (currentClick == 1) {
        end.x = mouseClickPos.x;
        end.y = mouseClickPos.y;
    }

    std::cout << "\n\nStart X: " << start.x << "\nStart Y: " << start.y;
    std::cout << "\n\nEnd X: " << end.x << "\nEnd Y: " << end.y;
    std::cout << "\n\nCurrentClick: " << currentClick;


    currentClick++;

    if (currentClick == 2) {
        if (currentTool == LINE)
            lines.emplace_back(start, end);

        if (currentTool == RECT) {
            int width = end.x - start.x;
            int height = end.y - start.y;

            drawRect(start, width, height, sf::Color::Yellow);
        }

        resetStartEnd();
    }
}

void Engine::resetStartEnd() {
    start.x = start.y = end.x = end.y = currentClick = 0;
}

// Gettery
PrimitiveRenderer Engine::getRenderer() {
    return this->primitiveRenderer;
}

// Funkcje do rysowania udostępniane
// tutaj dodawać kolejne funkcje rysowania jak drawLine(), drawRect() itp.

void Engine::setPixel(Point2D pos, sf::Color color) {
    //primitiveRenderer.setPixel(pos, color);
    Point2D newPoint(pos);
    points.push_back(newPoint);
}

void Engine::drawLine(Point2D start, Point2D end, sf::Color color) {
    //primitiveRenderer.drawLine(start, end, color);
    LineSegment newLine(start, end);
    lines.push_back(newLine);

}

void Engine::drawRect(Point2D start, int width, int height, sf::Color color, bool fill) {
    Rect newRect(start, width, height);
    rectangles.push_back(newRect);
}

void Engine::drawCircle(Point2D middle, int R, sf::Color color) {
    primitiveRenderer.drawCircle(middle, R, color);
}

void Engine::drawElipse(Point2D middle, int Rx, int Ry, sf::Color color) {
    primitiveRenderer.drawElipse(middle, Rx, Ry, color);
}

void Engine::drawPolygon(std::vector<Point2D> points, sf::Color color) {
    primitiveRenderer.drawPolygon(points, color);
}