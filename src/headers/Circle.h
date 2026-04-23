#pragma once

#include "Point2D.h"

class PrimitiveRenderer;

class Circle : public ShapeObject {
private:
	Point2D middle;
	int radius;
	sf::Color color;
	bool isFill;

public:
	Circle(Point2D mid, int r, sf::Color c = sf::Color::Cyan, bool fill = false) :
		middle(mid), radius(r), color(c), isFill(fill) { }

	// getters
	Point2D getPosition() { return this->middle; }
	int getRadius() { return this->radius; }
	sf::Color getColor() { return this->color; }

	// setters
	void setPosition(Point2D pos) { this->middle = pos; }
	void setRadius(int r) { this->radius = r; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};