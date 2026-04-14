#include <SFML/Graphics.hpp>
#include "headers/Point2D.h"
#include "headers/PrimitiveRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>

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

// Metody abstrakcyjne
void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.setPixel(*this, color);
}

void Point2D::translate(float dx, float dy) {
	this->setX(getX() + dx);
	this->setY(getY() - dy);
}

void Point2D::rotate(float angle, Point2D point) {
	float x1 = this->getX();
	float y1 = this->getY();
	int x0 = point.getX();
	int y0 = point.getY();

	float radians = angle * (M_PI / 180);

	float x2 = x0 + (x1 - x0) * cos(radians) - (y1 - y0) * sin(radians);
	float y2 = y0 + (x1 - x0) * sin(radians) + (y1 - y0) * cos(radians);

	// Ustawienie nowych wspolrzednych
	this->setX(x2);
	this->setY(y2);
}

void Point2D::scale(float k, Point2D point) {
	float x1 = this->getX();
	float y1 = this->getY();

	float x2 = x1 * k + (1 - k) * point.getX();
	float y2 = y1 * k + (1 - k) * point.getY();

	// Ustawienie nowych wspolrzednych
	this->setX(x2);
	this->setY(y2);
}