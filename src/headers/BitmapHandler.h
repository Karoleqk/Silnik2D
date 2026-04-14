#pragma once
#include <SFML/Graphics/Image.hpp>
#include <string>

class BitmapHandler {
private:
    sf::Image image;

public:
    BitmapHandler() = default;
    ~BitmapHandler() = default;

    void create(unsigned int width, unsigned int height, sf::Color color = sf::Color::Transparent);

    void destroy();

    bool loadFromFile(const std::string& filename);

    bool saveToFile(const std::string& filename) const;

    void copyFrom(const BitmapHandler& source, unsigned int destX, unsigned int destY,
        unsigned int sourceX = 0, unsigned int sourceY = 0,
        unsigned int sourceWidth = 0, unsigned int sourceHeight = 0);

    sf::Color getPixel(unsigned int x, unsigned int y) const;
    sf::Vector2u getSize() const;
};