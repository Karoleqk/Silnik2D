#include <SFML/Graphics.hpp>
#include "headers/Engine.h"
#include "headers/Drawer.h"
#include <vector>
#include <iostream>

int main()
{
    Engine engine; // engine bez parametrów: okno 800x600, z parematrami engine(x, y): okno x/y

    engine.setPixel(20, 20, sf::Color::White); // funkcja rysowania musi być wywołana przed engine.run();
    
    engine.drawLine(50, 50, 200, 50, sf::Color::White);

    engine.drawLine(100, 100, 300, 150, sf::Color::Blue);
    engine.drawLine(400, 100, 450, 400, sf::Color::Red);

    engine.drawRect(500, 50, 100, 50, sf::Color::Yellow);
    engine.drawRect(500, 200, 80, 80, sf::Color::Blue, true); // wypełniony

    engine.run(1000); // bez parametrów: 60fps, z paremetrem: wybrane fps
}