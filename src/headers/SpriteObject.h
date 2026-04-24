#pragma once

#include "BitmapObject.h"
#include "Point2D.h"

enum drawMode {SINGLE, BACKGROUND};

class PrimitiveRenderer;

/**
* @brief Klasa reprezentująca pojedynczy sprite na naszym ekranie
**/
class SpriteObject : public BitmapObject {
protected:
	/**
	* @brief Zmienna przechowująca wektor mapy
	**/
	std::vector<std::vector<int>> map;

	/**
	* @brief Skala obektu, domyślnie ustawione na 3
	**/
	float objectScale = 3.0f;

	/**
	* @brief Zmienna przechowująca aktualną klatkę animacji X
	**/
	int frameX = 0;

	/**
	* @brief Zmienna przechowująca aktualną klatkę animacji Y
	**/
	int frameY = 0;

	/**
	* @brief Zmienna przechowująca szerokość pojedynczej klatki
	**/
	int frameWidth = 32;

	/**
	* @brief Zmienna przechowująca wysokość pojedynczej klatki
	**/
	int frameHeight = 32;

public:
	/**
	* @brief Zmienna typu Point2D przechowująca aktualną pozycję sprite
	**/
	Point2D position;

	/**
	* @brief Zmienna przechowująca obecny tryb rysowanie, domyślnie ustawiony na SINGLE
	**/
	drawMode mode = SINGLE;

	int mapOffsetX = 0;

	void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;

	/**
	* @brief Metoda rysująca mapę
	* 
	* @param renderer - Referencja na istniejący obiekt rysowania
	**/
	void drawMap(PrimitiveRenderer& renderer);

	/**
	* @brief Metoda rysująca gracza
	* 
	* @param renderer - Referencja na istniejący obiekt rysowania
	**/
	void drawPlayer(PrimitiveRenderer& renderer);

	/**
	* @brief Metoda rysująca pojedynczą klatkę
	* 
	* @param renderer - Referencja na istniejący obiekt rysowania
	**/
	void drawFrame(PrimitiveRenderer& renderer);

	/**
	* @brief Metoda ustawiająca nową pozycję sprite
	* 
	* @parem pos - nowa pozycja sprite
	**/
	void setPosition(Point2D pos);

	/**
	* @brief Metoda ustawiająca mapę.
	* 
	* Jeśli mapa zostanie ustawiona, to aktualizujemy również tryb na BACKGROUND
	* oraz szerokość i wysokość pojedynczej klatki animacji na 16 pikseli
	**/
	void setMap(std::vector<std::vector<int>> map) {
		this->map = map;
		this->mode = BACKGROUND;
		this->frameWidth = this->frameHeight = 16;
	}

	/**
	* @brief Metoda ustawiająca aktualną klatkę sprite
	* 
	* @param x - numer wiersza w którym znajduje się nasza klatka
	* @parem y - numer kolumny w której znajduje się nasza klatka
	**/
	void setFrame(int x, int y) { frameX = x; frameY = y; }

	/**
	* @brief Metoda ustawiająca szerokość oraz wysokość pojedynczej klatki
	* 
	* @param w - szerokość klatki
	* @param h - wysokość klatki
	**/
	void setFrameSize(int w, int h) { frameWidth = w; frameHeight = h; }
};