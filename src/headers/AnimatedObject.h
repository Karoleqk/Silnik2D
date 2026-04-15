#pragma once

class AnimatedObject {
public:
	virtual void animate() = 0;
	virtual ~AnimatedObject() = default;
};