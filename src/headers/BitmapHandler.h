#pragma once
#include <SFML/Graphics/Image.hpp>
#include <string>

/**
* @brief Klasa implementująca metody operacji na bitmapach
**/
class BitmapHandler {
private:
    sf::Image image;

public:
    /**
    * @brief Tworzy obiekt do operacji na bitmapach
    **/
    BitmapHandler() = default;
    ~BitmapHandler() = default;

    /**
    * @brief Tworzenie nowej bitmapy koloru
    * 
    * @param width - szerokośc bitmapy
    * @param height - wysokość bitmapy
    * @param color - kolor, którym wypełniamy bitmapę (domyślnie transparentny)
    **/
    void create(unsigned int width, unsigned int height, sf::Color color = sf::Color::Transparent);

    /**
    * @brief Metoda usuwająca bitmapę
    **/
    void destroy();

    /**
    * @brief Metoda ładująca bitmapę z pliku
    * 
    * @parem filename - ścieżka do pliku, który posłuży nam za bitmapę
    **/
    bool loadFromFile(const std::string& filename);

    /**
    * @brief Metoda zapisująca bitmapę do pliku
    * 
    * @parem filename - nazwa pliku, do którego zapisujemy bitmapę
    **/
    bool saveToFile(const std::string& filename) const;

    /**
    * @brief Metoda kopiująca bitmapę z innego obiektu bitmap
    * 
    * @parem source - referencja na obiekt BitmapHandler od którego kopiujemy bitmapę
    * @parem destX - docelowa współrzędna X
    * @param destY - docelowa współrzędna Y
    * @param sourceX - współrzędna źródłowa X (domyślnie 0)
    * @param sourceY - współrzędna źródłowa Y (domyślnie 0)
    * @param sourceWidth - szerokość bitmapy źródłowej (domyślnie 0)
    * @param sourceHeight - wysokość bitmapy źródłowej (domyślnie 0)
    **/
    void copyFrom(const BitmapHandler& source, unsigned int destX, unsigned int destY,
        unsigned int sourceX = 0, unsigned int sourceY = 0,
        unsigned int sourceWidth = 0, unsigned int sourceHeight = 0);

    /**
    * @brief Metoda zwracająca kolor pojedynczego piksela
    * 
    * @param x - współrzędna x
    * @param y - współrzędna y
    * 
    * @return Kolor pożądanego piksela
    **/
    sf::Color getPixel(unsigned int x, unsigned int y) const;

    /**
    * @brief Metoda zwracająca rozmiar bitmapy
    * 
    * @return Rozmiar bitmapy typu Vector2u
    **/
    sf::Vector2u getSize() const;
};