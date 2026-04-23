#pragma once

#include "BitmapObject.h"
#include "Point2D.h"

enum drawMode {SINGLE, BACKGROUND};

class PrimitiveRenderer;

class SpriteObject : public BitmapObject {
protected:
	std::vector<std::vector<int>> map;

	float objectScale = 3.0f;

	int frameX = 0;
	int frameY = 0;

	int frameWidth = 32;
	int frameHeight = 32;

public:
	Point2D position;
	drawMode mode = SINGLE;

	int mapOffsetX = 0;

	void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;

	void drawMap(PrimitiveRenderer& renderer);
	void drawPlayer(PrimitiveRenderer& renderer);
	void drawFrame(PrimitiveRenderer& renderer);

	void setPosition(Point2D pos);
	void setMap(std::vector<std::vector<int>> map) {
		this->map = map;
		this->mode = BACKGROUND;
		this->frameWidth = this->frameHeight = 16;
	}
	void setFrame(int x, int y) { frameX = x; frameY = y; }
	void setFrameSize(int w, int h) { frameWidth = w; frameHeight = h; }
};