#include <SFML/Graphics.hpp>
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