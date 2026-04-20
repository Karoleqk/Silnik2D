#include "headers/Player.h"
#include "headers/PrimitiveRenderer.h"
#include <iostream>

Player::Player() : speed(2.0f) {}

void Player::update() {
    handleInput();

    velocityY -= gravity;

    int nextX = position.x + velocityX;
    int nextY = position.y - velocityY;

    // x
    if (!checkCollision(map, nextX, position.y)) {
        position.x = nextX;
    }

    // y
    if (!checkCollision(map, position.x, nextY)) {
        position.y = nextY;
    }
    else {
        velocityY = 0.0f;
        isJumping = false;
    }

    velocityX = 0.0f;

    int worldHeight = 600;
    int worldWidth = 800;

    // dół mapy
    if (position.y > worldHeight) {
        position.y = worldHeight;
        velocityY = 0;
        isJumping = false;
    }

    // lewa/prawa granica
    if (position.x < 0) position.x = 0;
    if (position.x > worldWidth) position.x = worldWidth;
}

void Player::handleInput() {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isJumping) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !isJumping)) {
        velocityY += jumpStrength;
        isJumping = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocityX -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocityX += speed;
    }
}

bool Player::checkCollision(std::vector<std::vector<int>>& map, int nextX, int nextY) {
    Rect playerRect = getRect(nextX, nextY);
    int tileSize = 16;

    int left = playerRect.start.x / tileSize;
    int right = (playerRect.start.x + playerRect.width) / tileSize;
    int top = playerRect.start.y / tileSize;
    int bottom = (playerRect.start.y + playerRect.height) / tileSize;

    std::cout << "map height: " << map.size() << std::endl;
    std::cout << "player tile Y: " << top << std::endl;

    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
            if (y < 0 || y >= map.size() || x < 0 || x >= map[0].size())
                continue;

            if (map[y][x] == 1)
                return true;
        }
    }

    return false;
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
    timer += dt;

    int maxFrames = (state == RUN) ? frameCountRun : frameCountIdle;

    if (timer >= frameTime) {
        timer = 0.f;

        frameX++;

        if (frameX >= maxFrames)
            frameX = 0;
    }
}

// Ustawianie

void Player::setPosition(Point2D pos) {
    position = pos;
}