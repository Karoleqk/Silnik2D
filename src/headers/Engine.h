#pragma once
#include "PrimitiveRenderer.h"
#include "Point2D.h"

enum tools {PIXEL, LINE, RECT, CIRCLE};

class Engine {
private:
	unsigned int width;
	unsigned int height;
	int currentTool;
	int currentClick;
	Point2D start, end;

	sf::RenderWindow window;
	PrimitiveRenderer primitiveRenderer;

	bool isDrawing;
	sf::Vector2i mouseClickPos;
public:
	Engine(unsigned int w = 800, unsigned int h = 600) : 
		width(w), height(h), window(sf::VideoMode({w, h}), "Silnik2D"), primitiveRenderer(window, width, height),
		isDrawing(false), currentTool(PIXEL), currentClick(0) {};

	void run(int fps = 60);
	void handleEvents();
	void update();

	// funkcja do ustawiania dwoch pozycji
	void drawShape();
	void resetStartEnd();

	// funkcje udostępnione do rysowania
	void setPixel(Point2D pos, sf::Color color);
	void drawLine(Point2D start, Point2D end, sf::Color color);
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);
};