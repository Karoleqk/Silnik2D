#pragma once

#include <SFML/Graphics.hpp>
class PrimitiveRenderer;

class DrawableObject {
public:
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) = 0;
};