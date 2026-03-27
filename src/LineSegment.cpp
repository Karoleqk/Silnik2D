#include "headers/LineSegment.h"
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"

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