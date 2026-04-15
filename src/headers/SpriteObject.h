#pragma once

#include "BitmapObject.h"
#include "Point2D.h"

class PrimitiveRenderer;

class SpriteObject : public BitmapObject {
protected:
	Point2D position;
	float scale = 3.0f;

	int frameX = 0;
	int frameY = 0;

	int frameWidth = 32;
	int frameHeight = 32;

	float timer = 0;
	float frameTime = 0.1f;

public:
	void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;
};