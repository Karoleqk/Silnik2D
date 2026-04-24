#pragma once

#include "Point2D.h"

/**
* @brief Klasa reprezentująca elipsę
**/
class Elipse : public ShapeObject {
private:
	Point2D middle;
	int radiusX, radiusY;
	sf::Color color;
	bool isFill;

public:

	/**
	* @brief Tworzy obiekt elipsy
	* 
	* @param m - środek elipsy
	* @param rX - promień po osi X
	* @param rY - promień po osi Y
	* @param c - kolor elipsy (domyślnie Cyan)
	* @param fill - definiuje czy obiekt ma byc wypełniony kolorem (domyślnie false)
	**/
	Elipse(Point2D m, int rX, int rY, sf::Color c = sf::Color::Cyan, bool fill = false) :
		middle(m), radiusX(rX), radiusY(rY), color(c), isFill(fill) { }


	/**
	* @brief Metoda zwracająca środek elipsy
	* 
	* @return Środek elipsy
	**/
	Point2D getPosition() { return this->middle; }

	/**
	* @brief Metoda zwracająca promień elipsy osi X
	* 
	* @return Promień osi X
	**/
	int getRadiusX() { return this->radiusX; }

	/**
	* @brief Metoda zwracająca promień elipsy Y
	* 
	* @return Promień osi Y
	**/
	int getRadiusY() { return this->radiusY; }

	/**
	* @brief Metoda zwracająca kolor elipsy
	* 
	* @return Kolor elipsy
	**/
	sf::Color getColor() { return this->color; }


	/**
	* @brief Metoda ustawiająca nowy środek elipsy
	* 
	* @param pos - Nowy środek elipsy
	**/
	void setPosition(Point2D pos) { this->middle = pos; }

	/**
	* @brief Metoda ustawiająca nowy promień X
	* 
	* @param rX - nowy promień osi X
	**/
	void setRadiusX(int rX) { this->radiusX = rX; }

	/**
	* @brief Metoda ustawiająca nowy promień Y
	* 
	* @param rY - nowy promień osi Y
	**/
	void setRadiusY(int rY) { this->radiusY = rY; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};