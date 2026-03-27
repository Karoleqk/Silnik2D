#pragma once

#include "PrimitiveRenderer.h"

class Point2D {
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

	// Metoda rysująca punkt
	void draw(PrimitiveRenderer& renderer, sf::Color color);
};