#include <SFML/Graphics.hpp>
#include <iostream>
#include "headers/Engine.h"
#include "headers/Drawer.h"

// Inicjalizacja okna (testowo narysowałem czerwony kwadrat)
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

// Funkcja do ogarniania eventów myszki/klawiatury, tutaj nic nie rysujemy, tylko rejestrujemy kliknięcia
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

// Funkcja do aktualizacji okna, najpierw czyścimy kolorem czarnym,
// potem renderujemy za pomocą klasy Drawer i robimy window.display() zeby wyswietlic
void Engine::update() {
    window.clear(sf::Color::Black);


    // jesli isDrawing = true, to rysujemy piksel tam, gdzie kliknelismy myszka
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

// Funkcje do rysowania udostępniane
// tutaj dodawać kolejne funkcje rysowania jak drawLine(), drawRect() itp.

void Engine::setPixel(int x, int y, sf::Color color) {
    drawer.setPixel(x, y, color);
}