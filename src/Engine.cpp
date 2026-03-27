#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/Drawer.h"

// Inicjalizacja okna (testowo narysowałem czerwony kwadrat)
void Engine::run(int fps) {
    isDrawing = false;
    window.setFramerateLimit(fps);

    //for (int i = 100; i < 200; i++)
    //    for (int j = 100; j < 200; j++)
    //        drawer.setPixel(i, j, sf::Color::Red);

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
                resetStartEnd();
                break;

            case sf::Keyboard::Key::Num2:
                currentTool = LINE;
                resetStartEnd();
                break;

            case sf::Keyboard::Key::Num3:
                currentTool = RECT;
                resetStartEnd();
                break;

            case sf::Keyboard::Key::Num4:
                currentTool = CIRCLE;
                resetStartEnd();
                break;
            }
        }
            
    }
}

// Funkcja do aktualizacji okna, najpierw czyścimy kolorem czarnym,
// potem renderujemy za pomocą klasy Drawer i robimy window.display() zeby wyswietlic
void Engine::update() {
    window.clear(sf::Color::Black);

    // jesli isDrawing = true, to rysujemy piksel tam, gdzie kliknelismy myszka
    if (isDrawing) {
        //std::cout << "Wcisnieto LPM\n";
        //std::cout << "X: " << mouseClickPos.x << "\nY: " << mouseClickPos.y << std::endl;
        //std::cout << window.getSize().x << "\n" << window.getSize().y << "\n";

        if (currentTool == PIXEL)
            setPixel({mouseClickPos.x, mouseClickPos.y}, sf::Color::Yellow);

        if (currentTool != PIXEL && currentTool != CIRCLE)
            drawShape();

        isDrawing = false;
    }

    drawer.render();

    window.display();
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
            drawLine(start, end, sf::Color::Yellow);

        if (currentTool == RECT) {
            if (start.x > end.x || start.y > end.y) {
                std::swap(start.x, end.x);
                std::swap(start.y, end.y);
            }

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
    drawer.setPixel(pos, color);
}

void Engine::drawLine(Point2D start, Point2D end, sf::Color color) {
    drawer.drawLine(start, end, color);
}

void Engine::drawRect(Point2D start, int width, int height, sf::Color color, bool fill) {
    drawer.drawRect(start, width, height, color, fill);
}