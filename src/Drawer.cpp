#include <SFML/Graphics.hpp>
#include "headers/Drawer.h"

void Drawer::setPixel(int x, int y, sf::Color color) {
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;

	sf::Vertex vertex;
	vertex.position = pos;
	vertex.color = color;

	sf::VertexArray va(sf::PrimitiveType::Points, 1);
	va[0] = vertex;

	window.draw(va);
}