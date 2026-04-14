#include "headers/LineSegment.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

// Getters
Point2D LineSegment::getStart() {
	return this->start;
}

Point2D LineSegment::getEnd() {
	return this->end;
}

// Setters
void LineSegment::setStart(Point2D pos) {
	this->start = pos;
}

void LineSegment::setEnd(Point2D pos) {
	this->end = pos;
}

// Metoda rysujaca
void LineSegment::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.drawLine(start, end, color);
}

void LineSegment::translate(float dx, float dy) {
	Point2D start = this->getStart(), end = this->getEnd();

	start.translate(dx, dy);
	end.translate(dx, dy);

	this->setStart(start);
	this->setEnd(end);
}

void LineSegment::rotate(float angle, Point2D point) {
	Point2D start = this->getStart(), end = this->getEnd();

	// zmiana wspolrzednych punktu startowego i koncowego
	// przy pomocy metody juz zaimplementowanej w Point2D
	start.rotate(angle, point);
	end.rotate(angle, point);

	this->setStart(start);
	this->setEnd(end);
}

void LineSegment::scale(float k, Point2D point) {
	Point2D start = this->getStart(), end = this->getEnd();

	start.scale(k, point);
	end.scale(k, point);

	this->setStart(start);
	this->setEnd(end);
}