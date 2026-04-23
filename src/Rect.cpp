#include "headers/Rect.h"
#include "headers/PrimitiveRenderer.h"

void Rect::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.drawRect(start, width, height, color, isFill);
}

void Rect::translate(float dx, float dy) {
	Point2D start = this->getStart();

	start.translate(dx, dy);

	this->setStart(start);
}

void Rect::rotate(float angle, Point2D point) {
	Point2D start = this->getStart();

	// zmiana wspolrzednych punktu startowego i koncowego
	// przy pomocy metody juz zaimplementowanej w Point2D
	start.rotate(angle, point);

	this->setStart(start);
}

void Rect::scale(float k, Point2D point) {
	Point2D start = this->getStart();

	start.scale(k, point);

	this->setStart(start);
}