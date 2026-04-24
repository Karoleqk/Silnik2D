#pragma once

#include "Point2D.h"

class PrimitiveRenderer;


/**
* @brief Klasa reprezentująca okrąg
**/
class Circle : public ShapeObject {
private:
	Point2D middle;
	int radius;
	sf::Color color;
	bool isFill;

public:

	/**
	* @brief Tworzy obiekt okręgu
	* 
	* @param mid - środek okręgu
	* @param r - promień okręgu
	* @param c - color okręgu (domyślnie Cyan)
	* @param fill - definiuje czy obiekt ma być wypełniony kolorem (domyślnie false)
	**/
	Circle(Point2D mid, int r, sf::Color c = sf::Color::Cyan, bool fill = false) :
		middle(mid), radius(r), color(c), isFill(fill) { }

	 
	/**
	* @brief Metoda zwracająca środek okręgu
	* 
	* @return Środek okręgu
	**/
	Point2D getPosition() { return this->middle; }

	/**
	* @brief Metoda zwracająca promień okręgu
	* 
	* @return Promień okręgu
	**/
	int getRadius() { return this->radius; }

	/**
	* @brief Metoda zwracająca kolor okręgu
	* 
	* @return Kolor okręgu
	**/
	sf::Color getColor() { return this->color; }


	/**
	* @brief Metoda ustawiająca nowy środek okręgu
	* 
	* @param pos - Nowy środek okręgu
	**/
	void setPosition(Point2D pos) { this->middle = pos; }

	/**
	* @brief Metoda ustawiająca nowy promień okręgu
	* 
	* @param r - nowy promień okręgu
	**/
	void setRadius(int r) { this->radius = r; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};