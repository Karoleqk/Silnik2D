#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class PrimitiveRenderer;

class DrawableObject : public GameObject {
public:
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) = 0;
};