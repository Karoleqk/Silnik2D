#include "headers/Player.h"
#include "headers/PrimitiveRenderer.h"
#include <iostream>

Player::Player() : speed(2.0f) {}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        position.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        position.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        position.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        position.x += speed;
    }
}

void Player::draw(PrimitiveRenderer& renderer, sf::Color color) {
    //renderer.drawCircle(position, 15, color);
    SpriteObject::draw(renderer, color);
}

void Player::translate(float dx, float dy) {
    position.translate(dx, dy);
}

void Player::rotate(float angle, Point2D point) {
    position.rotate(angle, point);
}

void Player::scale(float k, Point2D point) {
    position.scale(k, point);
}

void Player::animate(float dt) {
    SpriteObject::animate(dt);
}

// Ustawianie

void Player::setPosition(Point2D pos) {
    position = pos;
}