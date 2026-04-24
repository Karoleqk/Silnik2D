#pragma once
#include "GameObject.h"
//#include <math.h>

class Point2D;

/**
* @brief Klasa abstrakcyjna definiująca metody do przekształceń geometrycznych
**/
class TransformableObject : public GameObject {
public:
	/**
	* @brief Metoda translacji
	* 
	* Przesuwa obiekt o zadane wartości x oraz y
	* 
	* @param dx - przesunięcie osi X
	* @param dy - przesunięcie osi Y
	**/
	virtual void translate(float dx, float dy) = 0;

	/**
	* @brief Metoda rotacji
	* 
	* Obraca obiekt względem podanego punktu oraz o podany kąt
	* 
	* @param angle - kąt obrotu
	* @param point - punkt względem którego obracamy obiekt
	**/
	virtual void rotate(float angle, Point2D point) = 0;

	/**
	* @brief Metoda skalowanie
	* 
	* Skaluje obiekt o podaną wartość k względem podanego punktu
	* 
	* @param k - współczynnik skalowania
	* @param point - punkt względem którego skalujemy
	**/
	virtual void scale(float k, Point2D point) = 0; // Skalowanie
};