#pragma once

class Drawer {
private:
	unsigned int width;
	unsigned int height;

	std::vector<std::uint8_t> pixels;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow& window; // referencja do istniejacego okna

public:
	Drawer(sf::RenderWindow& win, unsigned int w, unsigned int h)
		: window(win), width(w), height(h), pixels(w * h * 4), texture(sf::Vector2u(width, height)), sprite(texture) {}

	void setPixel(int x, int y, sf::Color color);
	void render();
};