#pragma once
#include "PrimitiveRenderer.h"
#include "Point2D.h"
#include "LineSegment.h"
#include "Rect.h"
#include "Circle.h"
#include "Elipse.h"
#include "Player.h"
#include "headers/BitmapHandler.h"
#include "headers/BitmapObject.h"

enum tools {PIXEL, LINE, RECT, CIRCLE, FLOOD_FILL, BOUNDARY_FILL};

class Engine {
private:
	unsigned int width;
	unsigned int height;
	int currentTool;
	int currentClick;
	Point2D start, end;
	Player player;
	SpriteObject background;

	sf::RenderWindow window;
	PrimitiveRenderer primitiveRenderer;

	std::vector<LineSegment> lines;
	std::vector<Point2D> points;
	std::vector<Rect> rectangles;
	std::vector<Circle> circles;
	std::vector<Elipse> elipses;

	std::vector<std::vector<int>> map;

	bool isDrawing;
	sf::Vector2i mouseClickPos;
public:
	float angle = 1.0f;

	Engine(unsigned int w = 800, unsigned int h = 600);

	PrimitiveRenderer getRenderer();

	void run(int fps = 60);
	void handleEvents();
	void update();
	void render();

	// funkcja do ustawiania dwoch pozycji
	void drawShape();
	void resetStartEnd();

	// funkcje udostępnione do rysowania
	void setPixel(Point2D pos, sf::Color color);
	void drawLine(Point2D start, Point2D end, sf::Color color);
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);
	void drawCircle(Point2D middle, int R, sf::Color color, bool fill = false);
	void drawElipse(Point2D middle, int Rx, int Ry, sf::Color color, bool fill = false);
	void drawPolygon(std::vector<Point2D> points, sf::Color color);

	// Funkcje do obslugi zewnetrznej
	void setPlayer(Player& p) { this->player = p; }
	void setBackground(SpriteObject& b) { this->background = b; }

	// getter
	std::vector<std::vector<int>> getMap() { return this->map; }

	// setter
	void setMap(std::vector<std::vector<int>> m) { this->map = m; }
};