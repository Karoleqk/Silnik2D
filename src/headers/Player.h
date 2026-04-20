#pragma once
#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "AnimatedObject.h"
#include "Point2D.h"
#include "Rect.h"
#include <SFML/Window/Keyboard.hpp>

class Player : public UpdatableObject, public ShapeObject, public AnimatedObject {
private:
    std::vector<std::vector<int>> map;

    float speed;

    float velocityY = 0.0f;
    float velocityX = 0.0f;

    float gravity = 0.3f;
    float jumpStrength = 10.0f;
    bool isJumping = false;

public:
    Player();

    void update() override;

    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::Transparent) override;
    void translate(float dx, float dy) override;
    void rotate(float angle, Point2D point) override;
    void scale(float k, Point2D point) override;

    virtual void animate(float dt) override;

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


    bool checkCollision(std::vector<std::vector<int>>& map, int nextX, int nextY);

    // Metoda do ustawienia płótna
    void setPosition(Point2D pos);
    void setMap(std::vector<std::vector<int>> map) {
        this->map = map;
    }

    // poruszanie sie
    void handleInput();
    void handleCollision();
};