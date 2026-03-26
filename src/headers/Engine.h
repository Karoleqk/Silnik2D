#pragma once
#include "Drawer.h"

class Engine {
private:
	unsigned int width;
	unsigned int height;

	sf::RenderWindow window;
	Drawer drawer;

	bool isDrawing;
	sf::Vector2i mouseClickPos;
public:
	Engine(unsigned int w = 800, unsigned int h = 600) : 
		width(w), height(h), window(sf::VideoMode({w, h}), "Silnik2D"), drawer(window, width, height), isDrawing(false) {};

	void run(int fps = 60);
	void handleEvents();
	void update();

	// funkcje udostępnione do rysowania
	void setPixel(int x, int y, sf::Color color);
	void drawLine(int x0, int y0, int x1, int y1, sf::Color color);
	void drawRect(int x, int y, int width, int height, sf::Color color, bool fill = false);
};