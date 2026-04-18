#include "headers/SpriteObject.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/BitmapObject.h"
#include <iostream>


void SpriteObject::draw(PrimitiveRenderer& renderer, sf::Color color) {
    switch (mode) {
    case SINGLE:
        drawPlayer(renderer);
        break;
    case BACKGROUND:
        drawMap(renderer);
    }
}

void SpriteObject::setPosition(Point2D pos) {
    this->position = pos;
}

// Funkcje do rysowania
void SpriteObject::drawPlayer(PrimitiveRenderer& renderer) {
    drawFrame(renderer);
}

void SpriteObject::drawMap(PrimitiveRenderer& renderer) {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            int id = map[y][x];

            switch (id) {
            case 0:
                continue;
                break;
            case 1:
                frameX = 0;
                break;
            case 2:
                frameX = 1;
                break;
            }

            position.x = x * frameWidth * objectScale;
            position.y = y * frameHeight * objectScale;

            drawFrame(renderer);
        }
    }
}

void SpriteObject::drawFrame(PrimitiveRenderer& renderer) {
    int srcX = frameX * frameWidth;
    int srcY = frameY * frameHeight;

    for (int y = 0; y < frameHeight; y++) {
        for (int x = 0; x < frameWidth; x++) {

            sf::Color c = sheet.getPixel(srcX + x, srcY + y);

            if (c.a == 0) continue;

            for (int sy = 0; sy < (int)objectScale; sy++) {
                for (int sx = 0; sx < (int)objectScale; sx++) {
                    renderer.setPixel({
                        (int)position.x + (x * (int)objectScale + sx),
                        (int)position.y + (y * (int)objectScale + sy)
                        }, c);
                }
            }
        }
    }
}