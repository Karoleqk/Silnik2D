#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class PrimitiveRenderer;

class DrawableObject : virtual public GameObject {
public:
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) = 0;
};