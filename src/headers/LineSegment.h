#pragma once

#include <SFML/Graphics.hpp>
#include "Point2D.h"

class PrimitiveRenderer;

class LineSegment : ShapeObject {
	Point2D start;
	Point2D end;

public:
	LineSegment(Point2D s, Point2D e) : start(s), end(e) {};

	// Getters
	Point2D getStart();
	Point2D getEnd();

	// Setters
	void setStart(Point2D s);
	void setEnd(Point2D e);

	// Metoda rysująca
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = {0, 0}) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};