#include <SFML/Graphics.hpp>
#include "headers/Engine.h"
#include <vector>
#include <iostream>

int main()
{
    Engine engine; // engine bez parametrów: okno 800x600, z parematrami engine(x, y): okno x/y
    engine.run(1000); // bez parametrów: 60fps, z paremetrem: wybrane fps
}