#include "headers/Elipse.h"
#include "headers/PrimitiveRenderer.h"

void Elipse::draw(PrimitiveRenderer& renderer, sf::Color color) {
	renderer.drawElipse(middle, radiusX, radiusY, color, isFill);
}

void Elipse::translate(float dx, float dy) {
	Point2D start = this->getPosition();

	start.translate(dx, dy);

	this->setPosition(start);
}

void Elipse::rotate(float angle, Point2D point) {
	Point2D start = this->getPosition();

	// zmiana wspolrzednych punktu startowego i koncowego
	// przy pomocy metody juz zaimplementowanej w Point2D
	start.rotate(angle, point);

	this->setPosition(start);
}

void Elipse::scale(float k, Point2D point) {
	Point2D start = this->getPosition();

	start.scale(k, point);

	this->setPosition(start);
}