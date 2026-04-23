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
    int scaledW = frameWidth * objectScale;
    int scaledH = frameHeight * objectScale;

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            int id = map[y][x];

            if (id == 0) continue;
            else if (id == 1) frameX = 0;
            else if (id == 2) frameX = 1;

            position.x = x * scaledW - mapOffsetX + (scaledW / 2);
            position.y = (y + 1) * scaledH;

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

            int offsetX = frameWidth * objectScale / 2;
            int offsetY = frameHeight * objectScale / 2 + frameHeight;

            for (int sy = 0; sy < (int)objectScale; sy++) {
                for (int sx = 0; sx < (int)objectScale; sx++) {
                    renderer.setPixel({
                        (int)position.x + (x * (int)objectScale + sx) - offsetX,
                        (int)position.y + (y * (int)objectScale + sy - offsetY)
                        }, c);
                }
            }
        }
    }
}