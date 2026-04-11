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
		// żeby zmienić kolor tła, trzeba tutaj zrobić np.:
		// pixels[i * 4] = 120 -> ciemny czerwony kolor tła
		// analogicznie z innymi atrybutami:
		// pixels[i * 4], pixels[i * 4 + 1], pixels[i * 4 + 2]
		//		R					G				B
		pixels[i * 4 + 3] = 255; // A
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

void PrimitiveRenderer::drawPolygon(std::vector<Point2D> points, sf::Color color) {
	int n = points.size();
	if (n < 3) return; // Wielokąt musi mieć przynajmniej 3 wierzchołki


	auto orientation = [](Point2D p, Point2D q, Point2D r) {
		int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
		if (val == 0) return 0;
		return (val > 0) ? 1 : 2;
		};

	auto doIntersect = [&](Point2D p1, Point2D q1, Point2D p2, Point2D q2) {
		int o1 = orientation(p1, q1, p2);
		int o2 = orientation(p1, q1, q2);
		int o3 = orientation(p2, q2, p1);
		int o4 = orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4) return true;
		return false;
		};

	for (int i = 0; i < n; i++) {
		for (int j = i + 2; j < n; j++) {
			if (i == 0 && j == n - 1) continue;

			Point2D p1 = points[i];
			Point2D q1 = points[(i + 1) % n];
			Point2D p2 = points[j];
			Point2D q2 = points[(j + 1) % n];

			if (doIntersect(p1, q1, p2, q2)) {
				std::cout << "Odcinki figury sie przecinaja" << std::endl;
				return;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		drawLine(points[i], points[(i + 1) % n], color);
	}
}

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

// Aktualizuje bufor pikseli oraz renderuje je na okno
void PrimitiveRenderer::render() {
	texture.update(pixels.data());
	window.draw(sprite);
	window.display();
}