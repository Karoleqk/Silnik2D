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

struct GameEntity {
	SpriteObject sprite;
	Point2D position;
	int type; // 0 = moneta, 1 = slime
	bool active = true;
	int frameTimer = 0;
	int currentFrame = 0;
	int maxFrames = 1;
};

/**
* @brief Główna klasa silnika
**/
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

	sf::SoundBuffer coinBuffer;
	std::optional<sf::Sound> coinSound;

	sf::SoundBuffer hurtBuffer;
	std::optional<sf::Sound> hurtSound;
public:
	float angle = 1.0f;
	float globalSpeed = 3.5f;
	float distanceTraveled = 0.0f;
	/**
	* @brief zmienna przechowująca ilość zebranych monet
	**/
	int coinsCollected = 0;
	int mapOffsetX = 0;

	/**
	* @brief zmienna przechowująca uzyskany wynik
	**/
	int score = 0;

	/**
	* @brief zmienna boolowska definiująca koniec gry
	**/
	bool gameOver = false;

	/**
	* @brief wektor typu GameEntity przechowujący obiekty gry (monety, przeciwnicy)
	**/
	std::vector<GameEntity> entities;

	/**
	* @brief Bitmapa dla monet oraz przeciwników
	**/
	BitmapHandler coinBmp, slimeBmp;

	/**
	* @brief Tworzy główny obiekt silnika
	* 
	* @param w - szerokość okna (domyślnie 800)
	* @param h - wysokość okna (domyślnie 600)
	**/
	Engine(unsigned int w = 800, unsigned int h = 600);

	/**
	* @brief Metoda uruchamiająca silnik
	* 
	* @param fps - liczba klatek na sekundę
	**/
	void run(int fps = 60);

	/**
	* @brief Metoda nasłuchująca kliknięcia myszy oraz klawiatury
	**/
	void handleEvents();

	/**
	* @brief Metoda aktualizująca całą logikę silnika
	**/
	void update();

	/**
	* @brief Metoda renderująca obraz na ekran
	**/
	void render();

	/**
	* @brief Metoda resetująca grę
	**/
	void resetGame();

	/**
	* @brief Metoda pojawiająca obiekt gry na ekranie
	* 
	* @param type - typ obiektu (moneta / przeciwnik)
	* @param x - pozycja na osi X
	* @param y - pozycja na osi Y
	**/
	void spawnEntity(int type, int x, int y);

	/**
	* @brief Metoda dzięki której możemy za pomocą myszki narysować obiekty typu linia/kwadrat/okrąg
	**/
	void drawShape();

	/**
	* @brief Metoda resetująca zapisane pozycje naciśnięcia myszki
	**/
	void resetStartEnd();

	/**
	* @brief Metoda tworząca nowy obiekt typu Point2D i dodająca go do bufora renderowania
	* 
	* @param pos - pozycja punktu
	* @param color - kolor punktu
	**/
	void setPixel(Point2D pos, sf::Color color);

	/**
	* @brief Metoda tworząca nowy obiekt typu LineSegment i dodająca go do bufora renderowania
	* 
	* @param start - pozycja startowa
	* @param end - pozycja końcowa
	* @color - kolor linii
	**/
	void drawLine(Point2D start, Point2D end, sf::Color color);

	/**
	* @brief Metoda tworząca nowy obiekt typu Rect i dodająca go do bufora renderowania
	* 
	* @param start - pozycja startowa
	* @param width - szerokość
	* @param height - wysokość
	* @param color - kolor obiektu
	* @param fill - zmienna boolowska definiująca czy obiekt ma być wypełniony kolorem
	**/
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);

	/**
	* @brief Metoda tworząca nowy obiekt typu Circle i dodająca go do bufora renderowania
	* 
	* @param middle - środek okręgu
	* @param R - promień okręgu
	* @param color - kolor okręgu
	* @param fill - zmienna boolowska definiująca czy obiekt ma być wypełniony kolorem
	**/
	void drawCircle(Point2D middle, int R, sf::Color color, bool fill = false);

	/**
	* @brief Metoda tworząca nowy obiekt typu Elipse i dodająca go do bufora renderowania
	* 
	* @param middle - środek elipsy
	* @param Rx - promień osi X
	* @param Ry - promień osi Y
	* @param color - kolor elipsy
	* @param fill - zmienna boolowska definiująca czy obiekt ma być wypełniony kolorem
	**/
	void drawElipse(Point2D middle, int Rx, int Ry, sf::Color color, bool fill = false);

	void drawPolygon(std::vector<Point2D> points, sf::Color color);

	/**
	* @brief Metoda ustawiająca obiekt Player (gracz)
	* 
	* @param p - referencja do utworzonego obiektu Player
	**/
	void setPlayer(Player& p) { this->player = p; }

	/**
	* @brief Metoda ustawiająca obiekt SpriteObject (tło)
	* 
	* @param b - referencja do utworzonego obiektu SpriteObject
	**/
	void setBackground(SpriteObject& b) { this->background = b; }

	/**
	* @brief Metoda zwracająca wektor utworzonej w silniku mapy
	* 
	* @return wektor mapy
	**/
	std::vector<std::vector<int>> getMap() { return this->map; }

	/**
	* @brief Metoda ustawiająca wektor mapy
	* 
	* @param m - wektor mapy, który chcemy ustawić w naszym silniku
	**/
	void setMap(std::vector<std::vector<int>> m) { this->map = m; }
};