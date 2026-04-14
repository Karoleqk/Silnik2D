#pragma once

#include <SFML/Graphics.hpp>
#include "LineSegment.h"

class Point2D;

class PrimitiveRenderer {
private:
	unsigned int width;
	unsigned int height;

	std::vector<std::uint8_t> pixels;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow& window; // referencja do istniejacego okna

public:
	PrimitiveRenderer(sf::RenderWindow& win, unsigned int w, unsigned int h);

	void clear();
	void render();
	sf::Color getPixel(Point2D pos);

	void setPixel(Point2D pos, sf::Color color);
	void drawLine(Point2D start, Point2D end, sf::Color color);
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);
	void drawCircle(Point2D middle, int R, sf::Color color);
	void drawElipse(Point2D middle, int Rx, int Ry, sf::Color color);
	void drawPolygon(std::vector<Point2D> points, sf::Color color);

	void floodFill(Point2D pos, sf::Color fillColor, sf::Color bgColor);
	void boundaryFill(Point2D pos, sf::Color fillColor, sf::Color boundaryColor);
};