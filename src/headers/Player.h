#pragma once
#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "AnimatedObject.h"
#include "Point2D.h"
#include "Rect.h"
#include <optional>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>

/**
* @brief Klasa reprezentująca gracza
**/
class Player : public UpdatableObject, public ShapeObject, public AnimatedObject {
private:
    std::vector<std::vector<int>> map;

    float speed;

    float velocityY = 0.0f;
    float velocityX = 0.0f;

    float gravity = 0.3f;
    float jumpStrength = 10.0f;
    bool isJumping = false;

    sf::SoundBuffer jumpBuffer;
    std::optional<sf::Sound> jumpSound;

public:
    int mapOffsetX = 0;

    /**
    * @brief Tworzy obiekt reprezentujący gracza
    **/
    Player();

    void update() override;

    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;
    void translate(float dx, float dy) override;
    void rotate(float angle, Point2D point) override;
    void scale(float k, Point2D point) override;

    /**
    * @brief Metoda animująca ruch gracza
    * 
    * @param dt - szybkość animacji. Im większa wartość tym szybsza animacja
    **/
    virtual void animate(float dt) override;

    /**
    * @brief Metoda zwracająca obiekt typu Rect definiujący prostokąt wokół gracza
    * 
    * @return Obiekt typu Rect
    **/
    Rect getRect() {
        return getRect(position.x, position.y);
    }
    Rect getRect(int x, int y) {
        Rect r(
            { x - 16,
              y - 32 },
            32, 32
        );
        return r;
    }


    /**
    * @brief Metoda sprawdzająca kolizję z elementami mapy
    * 
    * @param map - referencja na mapę gry
    * @param nextX - następna pozycja gracza przy ruchu lewo/prawo
    * @param nextY - następna pozycja gracza przy ruchu góra/dół
    **/
    bool checkCollision(std::vector<std::vector<int>>& map, int nextX, int nextY);

    /**
    * @brief Metoda ustawiająca nową pozycję gracza
    * 
    * @param pos - nowa pozycja gracza
    **/
    void setPosition(Point2D pos);

    /**
    * @brief Metoda ustawiająca mapę gry w obiekcie gracza
    * 
    * @param map - mapa gry
    **/
    void setMap(std::vector<std::vector<int>> map) {
        this->map = map;
    }


    /**
    * @brief Metoda nasłuchująca ruch gracza
    **/
    void handleInput();
};