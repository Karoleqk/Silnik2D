#pragma once

#include "Point2D.h"

class Elipse : public ShapeObject {
private:
	Point2D middle;
	int radiusX, radiusY;
	sf::Color color;
	bool isFill;

public:
	Elipse(Point2D m, int rX, int rY, sf::Color c = sf::Color::Cyan, bool fill = false) :
		middle(m), radiusX(rX), radiusY(rY), color(c), isFill(fill) { }

	// getters
	Point2D getPosition() { return this->middle; }
	int getRadiusX() { return this->radiusX; }
	int getRadiusY() { return this->radiusY; }
	sf::Color getColor() { return this->color; }

	// setters
	void setPosition(Point2D pos) { this->middle = pos; }
	void setRadiusX(int rX) { this->radiusX = rX; }
	void setRadiusY(int rY) { this->radiusY = rY; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};