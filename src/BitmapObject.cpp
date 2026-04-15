#include "headers/BitmapObject.h"
#include "headers/PrimitiveRenderer.h"

void BitmapObject::draw(PrimitiveRenderer& renderer, sf::Color color) {
	sf::Vector2u size = sheet.getSize();

	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			sf::Color color = sheet.getPixel(x, y);

			if (color.a == 0)
				continue;

			renderer.setPixel({ (int)x, (int)y }, color);
		}
	}
}

void BitmapObject::setSheet(BitmapHandler& b) {
	this->sheet = b;
}