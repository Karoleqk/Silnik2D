#pragma once
#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "AnimatedObject.h"
#include "Point2D.h"
#include <SFML/Window/Keyboard.hpp>

class Player : public UpdatableObject, public ShapeObject, public AnimatedObject {
private:
    float speed;

    float velocityY = 0.0f;
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

    // Metoda do ustawienia płótna
    void setPosition(Point2D pos);

    // poruszanie sie
    void handleInput();
    void handleCollision();
};