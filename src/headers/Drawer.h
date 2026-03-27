#pragma once

#include "Point2D.h"

class Drawer {
private:
	unsigned int width;
	unsigned int height;

	std::vector<std::uint8_t> pixels;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow& window; // referencja do istniejacego okna

public:
	Drawer(sf::RenderWindow& win, unsigned int w, unsigned int h)
		: window(win), width(w), height(h), pixels(w * h * 4), texture(sf::Vector2u(width, height)), sprite(texture) {}

	void setPixel(Point2D pos, sf::Color color);
	void render();
	void drawLine(Point2D start, Point2D end, sf::Color color);
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);
};