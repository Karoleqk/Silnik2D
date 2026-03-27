#include <SFML/Graphics.hpp>
#include "headers/Point2D.h"
#include "headers/PrimitiveRenderer.h"

// Getters

int Point2D::getX() {
	return this->x;
}

int Point2D::getY() {
	return this->y;
}

// Setters

void Point2D::setX(int x) {
	this->x = x;
}

void Point2D::setY(int y) {
	this->y = y;
}

// Metoda rysujaca punkt

void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.setPixel(*this, color);
}