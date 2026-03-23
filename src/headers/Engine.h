#pragma once
#include "Drawer.h"

class Engine {
private:
	sf::RenderWindow window;
	Drawer drawer;

	bool isDrawing;
	sf::Vector2i mouseClickPos;
public:
	Engine() : window(sf::VideoMode({800, 600}), "Silnik2D"), drawer(window) {};

	void run(int fps = 60);
	void handleEvents();
	void update();
};