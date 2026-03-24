#include <SFML/Graphics.hpp>
#include "headers/Engine.h"
#include "headers/Drawer.h"
#include <vector>
#include <iostream>

int main()
{
    Engine engine; // engine bez parametrów: okno 800x600, z parematrami engine(x, y): okno x/y

    engine.setPixel(20, 20, sf::Color::White); // funkcja rysowania musi być wywołana przed engine.run();
    engine.run(1000); // bez parametrów: 60fps, z paremetrem: wybrane fps
}