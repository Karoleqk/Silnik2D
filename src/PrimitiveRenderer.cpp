#include <SFML/Graphics.hpp>
#include <cmath>
#include "headers/PrimitiveRenderer.h"
#include "headers/Point2D.h"
#include <iostream>
#include <stack>

#define _USE_MATH_DEFINES
#include <math.h>

PrimitiveRenderer::PrimitiveRenderer(sf::RenderWindow& win, unsigned int w, unsigned int h) :
	window(win),
	width(w),
	height(h),
	pixels(w* h * 4),
	texture(sf::Vector2u(width, height)),
	sprite(texture) {
	for (int i = 0; i < width * height; i++) {
		pixels[i * 4 + 3] = 255;
	}
}

// dodaje do bufora pikseli zmieniony kolor konkretnego pixela o wspolrzednych x,y
void PrimitiveRenderer::setPixel(Point2D pos, sf::Color color) {
	if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
		return;

	int index = 4 * (pos.y * width + pos.x);

	pixels[index] = color.r;
	pixels[index + 1] = color.g;
	pixels[index + 2] = color.b;
	pixels[index + 3] = color.a;
}

sf::Color PrimitiveRenderer::getPixel(Point2D pos) {
	if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
		return sf::Color::White;

	int index = 4 * (pos.y * width + pos.x);

	return sf::Color(
		pixels[index],
		pixels[index + 1],
		pixels[index + 2],
		pixels[index + 3]
	);
}

// |******************************|
// Funkcje do rysowania prymitywów
// |******************************|

// Zmiana argumentów z x0 y0 na Point2D start, x1 y1 na Point2D end
void PrimitiveRenderer::drawLine(Point2D start, Point2D end, sf::Color color) {
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

		for (int x = start.x; x <= end.x; ++x) {
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

void PrimitiveRenderer::drawRect(Point2D pos, int width, int height, sf::Color color, bool fill) {
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

void PrimitiveRenderer::drawCircle(Point2D middle, int R, sf::Color color) {
	int x = 0, y = R;
	int d = 3 - 2 * R;

	while (x <= y) {
		setPixel({middle.x + x, middle.y + y}, color);
		setPixel({middle.x - x, middle.y - y}, color);
		setPixel({middle.x - x, middle.y + y}, color);
		setPixel({middle.x + x, middle.y - y}, color);

		setPixel({middle.x + y, middle.y + x}, color);
		setPixel({middle.x - y, middle.y - x}, color);
		setPixel({middle.x + y, middle.y - x}, color);
		setPixel({middle.x - y, middle.y + x}, color);

		if (d < 0)
			d = d + 4 * x + 6;
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}

		x++;
	}
}

void PrimitiveRenderer::drawElipse(Point2D middle, int Rx, int Ry, sf::Color color) {
	int x, y;
	float i;

	float step = Rx > Ry ? 1.0 / Rx : 1.0 / Ry;

	

	for (i = 0; i < M_PI * 2; i += step) {
		x = middle.x + Rx * cos(i);
		y = middle.y + Ry * sin(i);
		
		setPixel({ x, y }, color);
	}
}

void PrimitiveRenderer::drawMultiAngle(std::vector<LineSegment> lines, sf::Color color) {
	
	for (auto line : lines) {
		std::cout << line.getStart().getX() << " ";
		std::cout << line.getStart().getY();

		std::cout << "\n";

		std::cout << line.getEnd().getX() << " ";
		std::cout << line.getEnd().getY();

		std::cout << "\n";

		drawLine(line.getStart(), line.getEnd(), color);
	}
}

// |******************************|

// Funkcja do wypełniania kolorem
void PrimitiveRenderer::floodFill(Point2D pos, sf::Color fillColor, sf::Color bgColor) {
	std::stack<Point2D> stack;
	stack.push(pos);

	while (!stack.empty()) {
		Point2D point = stack.top();
		stack.pop();

		sf::Color current = getPixel(point);

		if (current != bgColor) continue;
		if (current == fillColor) continue;
		
		if (current == bgColor) {
			setPixel(point, fillColor);

			stack.push({ point.x + 1, point.y });
			stack.push({ point.x - 1, point.y });
			stack.push({ point.x, point.y + 1 });
			stack.push({ point.x, point.y - 1 });
		}
	}
}


// |******************************|


// Aktualizuje bufor pikseli oraz renderuje je na okno
void PrimitiveRenderer::render() {
	texture.update(pixels.data());
	window.clear();
	window.draw(sprite);
}