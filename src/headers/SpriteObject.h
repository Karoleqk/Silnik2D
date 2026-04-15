#pragma once

#include "BitmapObject.h"
#include "AnimatedObject.h"
#include "Point2D.h"

enum AnimState {IDLE, RUN};

class PrimitiveRenderer;

class SpriteObject : public BitmapObject, public AnimatedObject {
protected:
	AnimState state = IDLE;

	Point2D position;
	float scale = 3.0f;

	int frameX = 0;
	int frameY = 0;

	int frameWidth = 32;
	int frameHeight = 32;

	float timer = 0;
	float frameTime = 0.1f;

	int frameCountIdle = 4;
	int frameCountRun = 16;

public:
	void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;
	virtual void animate(float dt) override;

	void setPosition(Point2D pos);
};