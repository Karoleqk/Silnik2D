#pragma once

#include <SFML/Graphics.hpp>
#include "ShapeObject.h"
class PrimitiveRenderer;

/**
* @brief Klasa reprezentująca pojedynczy piksel
**/
class Point2D : public ShapeObject {
public:
	/**
	* @brief zmienna przechowująca współrzędną X punktu
	**/
	int x;

	/**
	* @brief zmienna przechowująca współrzędną Y punktu
	**/
	int y;

	/**
	* @brief Tworzy obiekt reprezentujący pojedynczy piksel na ekranie
	* 
	* @param x - współrzędna X
	* @param y - współrzędna Y
	**/
	Point2D(int x = 0, int y = 0) : x(x), y(y) {};

	/**
	* @brief Metoda zwracająca pozycję X punktu
	* 
	* @return Współrzędna X
	**/
	int getX();


	/**
	* @brief Metoda zwracająca pozycję Y punktu
	* 
	* @return Współrzędna Y
	**/
	int getY();


	/**
	* @brief Metoda ustawiająca nową pozycję na osi X
	* 
	* @param x - nowa współrzędna X
	**/
	void setX(int x);

	/**
	* @brief Metoda ustawiająca nową pozycję na osi Y
	* 
	* @param y - nowa współrzędna Y
	**/
	void setY(int y);

	// Metody abstrakcyjne
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = {0, 0}) override;
	virtual void scale(float k = 1, Point2D point = {0, 0}) override;
};