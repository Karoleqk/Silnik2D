#pragma once

#include "Point2D.h"

class Rect : public ShapeObject{
public:
	int width, height;
	bool isFill;
	sf::Color color;
	Point2D start;

	Rect(Point2D s, int w, int h, sf::Color c = sf::Color::Cyan, bool fill = false) :
		start(s), width(w), height(h), color(c), isFill(fill) {}

	// Getters
	Point2D getStart() { return this->start; };
	sf::Color getColor() { return this->color; }
	int getWidth() { return this->width; }
	int getHeight() { return this->height; }

	// Setters
	void setStart(Point2D s) { this->start = s; };
	void setWidth(int w) { this->width = w; }
	void setHeight(int h) { this->height = h; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};