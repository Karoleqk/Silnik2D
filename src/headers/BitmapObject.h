#pragma once

#include "DrawableObject.h"
#include "TransformableObject.h"
#include "BitmapHandler.h"

class PrimitiveRenderer;

class BitmapObject : public DrawableObject {
protected:
	BitmapHandler sheet;

public:
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;

	void setSheet(BitmapHandler& b);
};