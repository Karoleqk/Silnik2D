#pragma once

#include <SFML/Graphics.hpp>
#include "Point2D.h"

class PrimitiveRenderer;

class LineSegment {
public:
	Point2D start;
	Point2D end;

	LineSegment(Point2D s, Point2D e) : start(s), end(e) {};

	// Getters
	Point2D getStart();
	Point2D getEnd();

	// Setters
	void setStart(Point2D s);
	void setEnd(Point2D e);

	// Metoda rysująca
	void draw(PrimitiveRenderer& renderer, sf::Color color);
};