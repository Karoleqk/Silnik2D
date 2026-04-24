#pragma once

#include "DrawableObject.h"
#include "TransformableObject.h"
#include "BitmapHandler.h"

class PrimitiveRenderer;

/**
* @brief Klasa reprezentująca obiekt bitmapy
**/
class BitmapObject : public DrawableObject {
protected:
	/**
	* @brief Zmienna przechowująca płótno bitmapy
	**/
	BitmapHandler sheet;

public:
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;

	/**
	* @brief Metoda ustawiająca nowe płótno obiektu bitmapy
	* 
	* @parem b - Referencja do obiektu BitmapHandler, którego chcemy ustawić jako płótno
	**/
	void setSheet(BitmapHandler& b);
};