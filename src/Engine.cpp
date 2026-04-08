#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"
#include "headers/LineSegment.h"

// Inicjalizacja okna (testowo narysowałem czerwony kwadrat)
void Engine::run(int fps) {
    isDrawing = false;
    window.setFramerateLimit(fps);

    // Do ogarniecia pozniej linie krzywe itd.

    //std::vector<LineSegment> tmp;
    //tmp.emplace_back(std::vector<Point2D>{50, 50}, std::vector<Point2D>{100, 100});
    //drawMultiAngle(tmp, sf::Color::Red);

    

    while (window.isOpen()) {
        handleEvents();
        update();
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
                currentTool = FILL;
                break;
            }

            resetStartEnd();
        }
            
    }
}

// Funkcja do aktualizacji okna, najpierw czyścimy kolorem czarnym,
// potem renderujemy za pomocą klasy Drawer i robimy window.display() zeby wyswietlic
void Engine::update() {
    // jesli isDrawing = true, to rysujemy piksel tam, gdzie kliknelismy myszka
    if (isDrawing) {
        //std::cout << "Wcisnieto LPM\n";
        //std::cout << "X: " << mouseClickPos.x << "\nY: " << mouseClickPos.y << std::endl;
        //std::cout << window.getSize().x << "\n" << window.getSize().y << "\n";

        if (currentTool == PIXEL) 
            points.emplace_back(mouseClickPos.x, mouseClickPos.y);
        
        if (currentTool == CIRCLE)
            drawCircle({ mouseClickPos.x, mouseClickPos.y }, 50, sf::Color::Yellow);

        if (currentTool != PIXEL && currentTool != CIRCLE && currentTool != FILL)
            drawShape();

        if (currentTool == FILL) {
            primitiveRenderer.floodFill({ mouseClickPos.x, mouseClickPos.y }, sf::Color::Red, sf::Color::Black);
        }

        isDrawing = false;
    }

    for (auto line : lines) {
        line.draw(primitiveRenderer, sf::Color::Cyan);
    }

    for (auto point : points) {
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

void Engine::drawMultiAngle(std::vector<LineSegment> lines, sf::Color color) {
    primitiveRenderer.drawMultiAngle(lines, color);
}