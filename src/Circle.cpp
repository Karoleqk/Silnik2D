#include "headers/Circle.h"
#include "headers/PrimitiveRenderer.h"

void Circle::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.drawCircle(middle, radius, color, isFill);
}

void Circle::translate(float dx, float dy) {
	Point2D start = this->getPosition();

	start.translate(dx, dy);

	this->setPosition(start);
}

void Circle::rotate(float angle, Point2D point) {
	Point2D start = this->getPosition();

	// zmiana wspolrzednych punktu startowego i koncowego
	// przy pomocy metody juz zaimplementowanej w Point2D
	start.rotate(angle, point);

	this->setPosition(start);
}

void Circle::scale(float k, Point2D point) {
	Point2D start = this->getPosition();

	start.scale(k, point);

	this->setPosition(start);
}