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

    BitmapHandler knight;
    knight.loadFromFile("C:/Dev/Grafika Komputerowa/repos/Silnik2D/assets/brackeys_platformer_assets/sprites/knight.png");
    Player player;
    player.setSheet(knight);
    engine.setPlayer(player);

    BitmapHandler bg;
    bg.loadFromFile("C:/Dev/Grafika Komputerowa/repos/Silnik2D/assets/brackeys_platformer_assets/sprites/world_tileset.png");
    SpriteObject background;
    background.setSheet(bg);

    std::vector<std::vector<int>> map;
    map = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    background.setMap(map);

    engine.setBackground(background);

    engine.drawLine({ 0, 500 }, {600, 500}, sf::Color::Blue);

    engine.run(240); // bez parametrów: 60fps, z paremetrem: wybrane fps
}