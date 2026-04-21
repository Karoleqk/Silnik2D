#include <SFML/Graphics.hpp>
#include "headers/Engine.h"
#include "headers/PrimitiveRenderer.h"
#include <vector>
#include <iostream>

int main()
{
    Engine engine; // engine bez parametrów: okno 800x600, z parematrami engine(x, y): okno x/y
    PrimitiveRenderer renderer = engine.getRenderer();

    BitmapHandler knight;
    knight.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sprites/knight.png");
    
    Player player;
    player.setSheet(knight);
    player.setMap(engine.getMap());
    player.setPosition({ 150, 240 });

    engine.setPlayer(player);

    BitmapHandler bg;
    bg.loadFromFile("C:/Users/kalcz/Documents/Projects/Silnik2D/assets/brackeys_platformer_assets/sprites/world_tileset.png");
    
    SpriteObject background;
    background.setSheet(bg);
    background.setMap(engine.getMap());

    engine.setBackground(background);

    engine.run(60); // bez parametrów: 60fps, z paremetrem: wybrane fps

    return 0;
}