#pragma once

#include <SFML/Graphics.hpp>
#include "LineSegment.h"

class Point2D;

/*
	@brief Klasa renderująca obraz na ekranie
*/
class PrimitiveRenderer {
private:
	unsigned int width;
	unsigned int height;

	std::vector<std::uint8_t> pixels;
	sf::Texture texture;
	sf::Sprite sprite;

	/**
	* @brief zmienna posiadające referencję do utworzonego okna
	**/
	sf::RenderWindow& window; // referencja do istniejacego okna

public:
	/**
		@brief Tworzy obiekt renderujący obraz na podanym oknie

		@param win - referencja na istniejący obiekt okna
		@param w - szerokość okna w pikselach
		@param h - wysokość okna w pikselach
	**/
	PrimitiveRenderer(sf::RenderWindow& win, unsigned int w, unsigned int h);

	/**
	* @brief Metoda czyszcząca bufor pikseli
	**/
	void clear();

	/**
	* @brief Metoda renderująca obraz na ekran
	**/
	void render();

	/**
	* @brief Metoda zwracająca kolor piksela w podanej pozycji
	* 
	* @param pos - pozycja piksela, którego kolor chcemy uzyskać
	* 
	* @return kolor piksela
	**/
	sf::Color getPixel(Point2D pos);

	/**
	* @brief Metoda ustawiająca piksel o przekazanej pozycji na podany kolor
	* 
	* @param pos - pozycja piksela, którego kolor chcemy zmienić
	* @param color - kolor, na który zmienimy nasz piksel
	**/
	void setPixel(Point2D pos, sf::Color color);

	/**
	* @brief Metoda rysująca linię na ekranie
	* 
	* @param start - pozycja startowa
	* @param end - pozycja końcowa
	* @param color - kolor linii
	**/
	void drawLine(Point2D start, Point2D end, sf::Color color);

	/**
	* @brief Metoda rysująca kwadrat/prostokąt na ekranie
	* 
	* @param start - pozycja startowa
	* @param width - szerokość figury
	* @param height - wysokość figury
	* @param color - kolor figury
	* @param fill - wartość boolowska definiująca czy figura ma być wypełniona kolorem. Domyślnie false
	**/
	void drawRect(Point2D start, int width, int height, sf::Color color, bool fill = false);

	/**
	* @brief Metoda rysując okrąg na ekranie
	* 
	* @param middle - środek okręgu
	* @param R - promień okręgu
	* @param color - kolor okręgu
	* @param fill - wartość boolowska definiująca czy okrąg ma być wypełniony kolorem. Domyślnie false
	**/
	void drawCircle(Point2D middle, int R, sf::Color color, bool fill = false);

	/**
	* @brief Metoda rysująca elipsę na ekranie
	* 
	* @param middle - środek elipsy
	* @param Rx - promień osi X
	* @param Ry - promień osi Y
	* @param color - kolor elipsy
	* @param fill - wartość boolowska definiująca czy elipsa ma być wypełniona kolorem. Domyślnie false
	**/
	void drawElipse(Point2D middle, int Rx, int Ry, sf::Color color, bool fill = false);

	void drawPolygon(std::vector<Point2D> points, sf::Color color);

	/**
	* @brief Metoda wypełniania kolorem algorytmem Flood Fill
	* 
	* @param pos - pozycja, od której zaczynamy wypełniać kolorem
	* @param fillColor - kolor, którym wypełniamy
	* @param bgColor - kolor, który chcemy zastąpić naszym kolorem wypełniania
	**/
	void floodFill(Point2D pos, sf::Color fillColor, sf::Color bgColor);

	/**
	* @brief Metoda wypełniania kolorem algorytmem Boundary Fill
	* 
	* @param pos - pozycja, od której zaczynamy wypełniać kolorem
	* @param fillColor - kolor, którym wypełniamy
	* @param boundaryColor - kolor krawędzi wypełnianego obszaru
	**/
	void boundaryFill(Point2D pos, sf::Color fillColor, sf::Color boundaryColor);
};