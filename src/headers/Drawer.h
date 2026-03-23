#pragma once

class Drawer {
private:
	sf::RenderWindow& window; // referencja do istniejacego okna

public:
	Drawer(sf::RenderWindow& win) : window(win) {}

	void setPixel(int x, int y, sf::Color color);
};