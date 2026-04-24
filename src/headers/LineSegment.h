#pragma once

#include <SFML/Graphics.hpp>
#include "Point2D.h"

class PrimitiveRenderer;


/**
* @brief Klasa reprezentująca linię
**/
class LineSegment : public ShapeObject {
	Point2D start;
	Point2D end;
	sf::Color color;

public:
	/**
	* @brief Tworzy obiekt reprezentujący linię na ekranie
	* 
	* @param s - pozycja startowa
	* @param e - pozycja końcowa
	* @param c - kolor linii (domyślnie Cyan)
	**/
	LineSegment(Point2D s, Point2D e, sf::Color c = sf::Color::Cyan) :
		start(s), end(e), color(c) {};


	/**
	* @brief Metoda zwracająca pozycję startową linii
	* 
	* @return Pozycja startowa linii typu Point2D
	**/
	Point2D getStart();

	/**
	* @brief Metoda zwracająca pozycję końcową linii
	* 
	* @return Pozycja końcowa linii typu Point2D
	**/
	Point2D getEnd();


	/**
	* @brief Metoda zwracająca kolor linii
	* 
	* @return Kolor linii
	**/
	sf::Color getColor() { return this->color; }

	/**
	* @brief Metoda ustawiająca nową pozycję startową linii
	* 
	* @param s - nowy punkt startowy typu Point2D
	**/
	void setStart(Point2D s);

	/**
	* @brief Metoda ustawiająca nową pozycję końcową linii
	* 
	* @param e - nowy punkt końcowy typu Point2D
	**/
	void setEnd(Point2D e);

	// Metoda rysująca
	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = {0, 0}) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};