#pragma once

#include "SpriteObject.h"

enum AnimState { IDLE, RUN };

class AnimatedObject : public SpriteObject {
protected:
	/**
	* @brief Zmienna przechowująca tryb poruszania się (IDLE = 0, RUN = 1)
	**/
	AnimState state = IDLE;

	/**
	* @brief Zmienna czasu, potrzebna przy animacji obiektu
	**/
	float timer = 0;

	/**
	* @brief Zmienna określająca czas pojedynczej klatki animacji
	**/
	float frameTime = .1f;

	/**
	* @brief Zmienna przechowująca ilość klatek animacji IDLE
	**/
	int frameCountIdle = 4;

	/**
	* @brief Zmienna przechowująca ilość klatek animacji RUN
	**/
	int frameCountRun = 16;

public:
	virtual void animate(float dt) = 0;
};