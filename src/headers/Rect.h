#pragma once

#include "Point2D.h"

class Rect : ShapeObject{
public:
	Point2D start;
	int width, height;

	Rect(Point2D s, int w, int h) :
		start(s), width(w), height(h) {}

	// Getters
	Point2D getStart() { return this->start; };

	// Setters
	void setStart(Point2D s) { this->start = s; };

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};