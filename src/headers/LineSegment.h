#pragma once

#include <SFML/Graphics.hpp>
#include "Point2D.h"

class PrimitiveRenderer;

class LineSegment : public ShapeObject {
	Point2D start;
	Point2D end;
	sf::Color color;

public:
	LineSegment(Point2D s, Point2D e, sf::Color c = sf::Color::Cyan) :
		start(s), end(e), color(c) {};

	// Getters
	Point2D getStart();
	Point2D getEnd();
	sf::Color getColor() { return this->color; }

	// Setters
	void setStart(Point2D s);
	void setEnd(Point2D e);

	// Metoda rysująca
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = {0, 0}) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};