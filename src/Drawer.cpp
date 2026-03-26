#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/Drawer.h"

// dodaje do bufora pikseli zmieniony kolor konkretnego pixela o wspolrzednych x,y
void Drawer::setPixel(int x, int y, sf::Color color) {
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	int index = 4 * (y * width + x);

	pixels[index] = color.r;
	pixels[index + 1] = color.g;
	pixels[index + 2] = color.b;
	pixels[index + 3] = color.a;
}


// Aktualizuje bufor pikseli oraz renderuje je na okno
void Drawer::render() {
	texture.update(pixels.data());
	window.draw(sprite);
}

void Drawer::drawLine(int x0, int y0, int x1, int y1, sf::Color color) {
	float dx = x1 - x0;
	float dy = y1 - y0;

	// przypadek gdy początek i koniec to to samo miejsce
	if (dx == 0 && dy == 0) {
		setPixel(x0, y0, color);
		return;
	}

	// obliczanie nachylenia
	// pierwszy if dla |m| <= 1, linia bardziej pozioma
	// drugi dla |m| > 1, bardziej pionowa
	if (std::abs(dx) >= std::abs(dy)) {
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		float m = dy / dx;
		float y = y0;

		for (int x = x0; x <= x1; x++) {
			setPixel(x, std::round(y), color);
			y += m;
		}
	}
	else {
		if (y0 > y1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		float m = dx / dy;
		float x = x0;

		for (int y = y0; y <= y1; y++) {
			setPixel(std::round(x), y, color);
			x += m;
		}
	}
}

void Drawer::drawRect(int x, int y, int width, int height, sf::Color color, bool fill) {
	if (fill) {
		for (int i = 0; i <= width; i++)
			for (int j = 0; j <= height; j++)
				setPixel(x + i, y + j, color);
	}
	else {
		drawLine(x, y, x + width, y, color); // góra
		drawLine(x, y + height, x + width, y + height, color); // dół
		drawLine(x, y, x, y + height, color); // lewa
		drawLine(x + width, y, x + width, y + height, color); //prawa
	}
}