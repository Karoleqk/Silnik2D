#include "headers/Player.h"
#include "headers/PrimitiveRenderer.h"

Player::Player(int startX, int startY) : position(startX, startY), speed(5.0f) {}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        translate(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        translate(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        translate(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        translate(speed, 0);
    }
}

void Player::draw(PrimitiveRenderer& renderer, sf::Color color) {
    renderer.drawCircle(position, 15, color);
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