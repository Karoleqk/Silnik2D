#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class PrimitiveRenderer;

/**
* @brief Klasa abstrakcyjna wykorzystywana do rysowania obiektów
**/
class DrawableObject : public GameObject {
public:
	/**
	* @brief Metoda potrzebna do rysowania obiektów
	* 
	* @param renderer - referencja na obiekt renderowania
	* @param color - kolor, którym rysujemy nasz obiekt
	**/
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) = 0;
};