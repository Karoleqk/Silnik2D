#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/Drawer.h"

void Engine::run(int fps) {
    isDrawing = false;
    window.setFramerateLimit(fps);

    for (int i = 100; i < 200; i++)
        for (int j = 100; j < 200; j++)
            drawer.setPixel(i, j, sf::Color::Red);

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
    window.clear(sf::Color::Black);

    if (isDrawing) {
        std::cout << "Wcisnieto LPM\n";
        std::cout << "X: " << mouseClickPos.x << "\nY: " << mouseClickPos.y << std::endl;
        std::cout << window.getSize().x << "\n" << window.getSize().y;

        drawer.setPixel(mouseClickPos.x, mouseClickPos.y, sf::Color::Yellow);

        isDrawing = false;
    }

    drawer.render();

    window.display();
}