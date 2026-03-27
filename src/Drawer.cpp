#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/Drawer.h"

// dodaje do bufora pikseli zmieniony kolor konkretnego pixela o wspolrzednych x,y
void Drawer::setPixel(Point2D pos, sf::Color color) {
	if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
		return;

	int index = 4 * (pos.y * width + pos.x);

	pixels[index] = color.r;
	pixels[index + 1] = color.g;
	pixels[index + 2] = color.b;
	pixels[index + 3] = color.a;
}

// Zmiana argumentów z x0 y0 na Point2D start, x1 y1 na Point2D end
void Drawer::drawLine(Point2D start, Point2D end, sf::Color color) {
	float dx = end.x - start.x;
	float dy = end.y - start.y;

	// przypadek gdy początek i koniec to to samo miejsce
	if (dx == 0 && dy == 0) {
		setPixel(start, color);
		return;
	}

	// obliczanie nachylenia
	// pierwszy if dla |m| <= 1, linia bardziej pozioma
	// drugi dla |m| > 1, bardziej pionowa
	if (std::abs(dx) >= std::abs(dy)) {
		if (start.x > end.x) {
			std::swap(start.x, end.x);
			std::swap(start.y, end.y);
		}

		float m = dy / dx;
		float y = start.y;

		for (int x = start.x; x <= end.x; x++) {
			//setPixel(x, std::round(y), color);
			setPixel({ x, static_cast<int>(std::round(y)) }, color);
			y += m;
		}
	}
	else {
		if (start.y > end.y) {
			std::swap(start.x, end.x);
			std::swap(start.y, end.y);
		}

		float m = dx / dy;
		float x = start.x;

		for (int y = start.y; y <= end.y; y++) {
			//setPixel(std::round(x), y, color);
			setPixel({ static_cast<int>(std::round(x)), y }, color);
			x += m;
		}
	}
}

void Drawer::drawRect(Point2D pos, int width, int height, sf::Color color, bool fill) {
	if (fill) {
		for (int i = 0; i <= width; i++)
			for (int j = 0; j <= height; j++)
				setPixel({ pos.x + i, pos.y + j }, color);
	}
	else {
		drawLine({ pos.x, pos.y }, { pos.x + width, pos.y }, color); // góra
		drawLine({ pos.x, pos.y + height }, { pos.x + width, pos.y + height }, color); // dół
		drawLine({ pos.x, pos.y }, { pos.x, pos.y + height }, color); // lewa
		drawLine({ pos.x + width, pos.y }, { pos.x + width, pos.y + height }, color); //prawa
	}
}

// Aktualizuje bufor pikseli oraz renderuje je na okno
void Drawer::render() {
	texture.update(pixels.data());
	window.draw(sprite);
}