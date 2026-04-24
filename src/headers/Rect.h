#pragma once

#include "Point2D.h"


/**
* @brief Klasa reprezentująca kwadrat/prostokąt
**/
class Rect : public ShapeObject{
public:
	/**
	* @brief Szerokość obiektu
	**/
	int width;

	/**
	* @brief Wysokość obiektu
	**/
	int height;

	/**
	* @brief Zmienna przechowująca informację czy obiekt ma być wypełniony kolorem
	**/
	bool isFill;

	/**
	* @brief kolor obiektu
	**/
	sf::Color color;

	/**
	* @brief Punkt startowy obiektu
	**/
	Point2D start;

	/**
	* @brief Tworzy obiekt kwadratu/prostokątu
	* 
	* @param s - pozycja startowa
	* @param w - szerokość
	* @param h - wysokość
	* @param c - kolor obiektu (domyślnie Cyan)
	* @param fill - definiuje czy obiekt ma być wypełniony kolorem (domyślnie false)
	**/
	Rect(Point2D s, int w, int h, sf::Color c = sf::Color::Cyan, bool fill = false) :
		start(s), width(w), height(h), color(c), isFill(fill) {}


	/**
	* @brief Metoda zwracająca pozycję startową
	* 
	* @return Pozycja startowa typu Point2D
	**/
	Point2D getStart() { return this->start; };

	/**
	* @brief Metoda zwracająca kolor obiektu
	* 
	* @return Kolor obiektu
	**/
	sf::Color getColor() { return this->color; }

	/**
	* @brief Metoda zwracająca szerokość
	* 
	* @return Szerokość obiektu
	**/
	int getWidth() { return this->width; }

	/**
	* @brief Metoda zwracająca wysokość
	* 
	* @return Wysokośc obiektu
	**/
	int getHeight() { return this->height; }

	

	/**
	* @brief Metoda ustawiająca nową pozycję startową
	* 
	* @param s - Nowa pozycja startowa
	**/
	void setStart(Point2D s) { this->start = s; };

	/**
	* @brief Metoda ustawiająca nową szerokość
	* 
	* @param w - Nowa szerokość
	**/
	void setWidth(int w) { this->width = w; }

	/**
	* @brief Metoda ustawiająca nową wysokość
	* 
	* @param h - nowa wysokość
	**/
	void setHeight(int h) { this->height = h; }

	virtual void draw(PrimitiveRenderer& renderer, sf::Color color) override;
	virtual void translate(float dx, float dy) override;
	virtual void rotate(float angle = 0.0f, Point2D point = { 0, 0 }) override;
	virtual void scale(float k = 1, Point2D point = { 0, 0 }) override;
};