#pragma once
#include "UpdatableObject.h"
#include "ShapeObject.h"
#include "Point2D.h"
#include <SFML/Window/Keyboard.hpp>

class Player : public UpdatableObject, public ShapeObject {
private:
    Point2D position;
    float speed;

public:
    Player(int startX, int startY);

    void update() override;

    void draw(PrimitiveRenderer& renderer, sf::Color color) override;
    void translate(float dx, float dy) override;
    void rotate(float angle, Point2D point) override;
    void scale(float k, Point2D point) override;
};