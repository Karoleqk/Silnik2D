#include "headers/BitmapHandler.h"
#include <iostream>

void BitmapHandler::create(unsigned int width, unsigned int height, sf::Color color) {
    image.resize({ width, height });
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            image.setPixel({ x, y }, color);
        }
    }
}

void BitmapHandler::destroy() {
    image = sf::Image();
}

bool BitmapHandler::loadFromFile(const std::string& filename) {
    if (!image.loadFromFile(filename)) {
        std::cerr << "Failed to load " << filename << std::endl;
        return false;
    }
    return true;
}

bool BitmapHandler::saveToFile(const std::string& filename) const {
    if (!image.saveToFile(filename)) {
        std::cerr << "Failed to save " << filename << std::endl;
        return false;
    }
    return true;
}

void BitmapHandler::copyFrom(const BitmapHandler& source, unsigned int destX, unsigned int destY,
    unsigned int sourceX, unsigned int sourceY,
    unsigned int sourceWidth, unsigned int sourceHeight) {

    sf::Vector2u srcSize = source.getSize();

    unsigned int copyWidth = (sourceWidth == 0) ? srcSize.x - sourceX : sourceWidth;
    unsigned int copyHeight = (sourceHeight == 0) ? srcSize.y - sourceY : sourceHeight;

    for (unsigned int y = 0; y < copyHeight; ++y) {
        for (unsigned int x = 0; x < copyWidth; ++x) {

            if (destX + x < image.getSize().x && destY + y < image.getSize().y &&
                sourceX + x < srcSize.x && sourceY + y < srcSize.y) {

                sf::Color pixelColor = source.getPixel(sourceX + x, sourceY + y);
                image.setPixel({ destX + x, destY + y }, pixelColor);
            }
        }
    }
}

sf::Color BitmapHandler::getPixel(unsigned int x, unsigned int y) const {
    if (x < image.getSize().x && y < image.getSize().y) {
        return image.getPixel({ x, y });
    }
    return sf::Color::Transparent;
}

sf::Vector2u BitmapHandler::getSize() const {
    return image.getSize();
}