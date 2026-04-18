#pragma once

#include "SpriteObject.h"

enum AnimState { IDLE, RUN };

class AnimatedObject : public SpriteObject {
protected:
	AnimState state = IDLE;

	float timer = 0;
	float frameTime = .1f;

	int frameCountIdle = 4;
	int frameCountRun = 16;

public:
	virtual void animate(float dt) = 0;
};