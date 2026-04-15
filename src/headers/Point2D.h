#pragma once

#include <SFML/Graphics.hpp>
#include "ShapeObject.h"
class PrimitiveRenderer;

class Point2D : public ShapeObject {
public:
	int x;
	int y;

	Point2D(int x = 0, int y = 0) : x(x), y(y) {};

	// Getters
	int getX();
	int getY();

	// Setters
	void setX(int x);
	void setY(int y);

	// Metody abstrakcyjne
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = {0, 0}) override;
	virtual void scale(float k = 1, Point2D point = {0, 0}) override;
};