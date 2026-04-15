#include <SFML/Graphics.hpp>
#include "headers/Engine.h"
#include "headers/PrimitiveRenderer.h"
#include <vector>
#include <iostream>

int main()
{
    Engine engine; // engine bez parametrów: okno 800x600, z parematrami engine(x, y): okno x/y
    PrimitiveRenderer renderer = engine.getRenderer();
    Point2D point(50, 50);

    BitmapHandler bmp;
    bmp.loadFromFile("C:/Dev/Grafika Komputerowa/repos/Silnik2D/assets/brackeys_platformer_assets/sprites/knight.png");
    Player player;
    player.setSheet(bmp);
    player.setPosition({ 400, 300 });
    engine.setPlayer(player);

    engine.run(240); // bez parametrów: 60fps, z paremetrem: wybrane fps
}