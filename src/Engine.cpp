#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/Drawer.h"

void Engine::run(int fps = 60) {
    isDrawing = false;
    window.setFramerateLimit(fps);

    while (window.isOpen()) {
        handleEvents();
        update();
    }
}

void Engine::handleEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            auto pos = sf::Mouse::getPosition(window);

            mouseClickPos = pos;
            isDrawing = true;
        }
            
    }
}

void Engine::update() {
    if (isDrawing) {
        std::cout << "Wcisnieto LPM\n";
        std::cout << "X: " << mouseClickPos.x << "\nY: " << mouseClickPos.y << std::endl;

        drawer.setPixel(mouseClickPos.x, mouseClickPos.y, sf::Color::Blue);

        isDrawing = false;
    }

    window.display();
}