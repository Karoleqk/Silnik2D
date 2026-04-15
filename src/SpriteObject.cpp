#include "headers/SpriteObject.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/BitmapObject.h"
#include <iostream>


void SpriteObject::draw(PrimitiveRenderer& renderer, sf::Color color) {
    int srcX = frameX * frameWidth;
    int srcY = frameY * frameHeight;
    int s = (int)scale;

    for (int y = 0; y < frameHeight; y++) {
        for (int x = 0; x < frameWidth; x++) {

            sf::Color c = sheet.getPixel(srcX + x, srcY + y);

            if (c.a == 0)
                continue;

            // SCALE PIXELA
            for (int sy = 0; sy < s; sy++) {
                for (int sx = 0; sx < s; sx++) {

                    renderer.setPixel(
                        {
                            (int)position.x + (x * s + sx),
                            (int)position.y + (y * s + sy)
                        },
                        c
                    );
                }
            }
        }
    }
}