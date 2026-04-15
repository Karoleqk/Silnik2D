#pragma once
#include "GameObject.h"
//#include <math.h>

class Point2D;

class TransformableObject : public GameObject {
	virtual void translate(float dx, float dy) = 0; // Przesunięcie
	virtual void rotate(float angle, Point2D point) = 0; // Obrót
	virtual void scale(float k, Point2D point) = 0; // Skalowanie
};