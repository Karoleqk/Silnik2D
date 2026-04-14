#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"
#include "headers/LineSegment.h"

// Inicjalizacja okna (testowo narysowałem czerwony kwadrat)
void Engine::run(int fps) {
    window.setFramerateLimit(fps);

    std::vector<Point2D> quad = {
        Point2D(400, 300),
        Point2D(500, 400),
        Point2D(400, 500),
        Point2D(600, 400)
    };
    //drawPolygon(quad, sf::Color::Yellow);

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

// Funkcja do ogarniania eventów myszki/klawiatury, tutaj nic nie rysujemy, tylko rejestrujemy kliknięcia
void Engine::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        // Klikniecia myszki
        if (auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                auto pos = sf::Mouse::getPosition(window);
                mouseClickPos = pos;
                isDrawing = true;
            }
        }


        // Wybór narzędzia
        if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
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
            }

            resetStartEnd();
        }
            
    }
}

// Metoda do aktualizowania zmiennych
void Engine::update() {
    player.update();

    Point2D middle(400, 300);
    points.push_back(middle);

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
    player.draw(primitiveRenderer, sf::Color::Green);

    for (auto& line : lines) {
        line.draw(primitiveRenderer, sf::Color::Cyan);
    }

    for (auto& point : points) {
        point.draw(primitiveRenderer, sf::Color::Cyan);
    }

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
    primitiveRenderer.setPixel(pos, color);
}

void Engine::drawLine(Point2D start, Point2D end, sf::Color color) {
    primitiveRenderer.drawLine(start, end, color);
}

void Engine::drawRect(Point2D start, int width, int height, sf::Color color, bool fill) {
    primitiveRenderer.drawRect(start, width, height, color, fill);
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