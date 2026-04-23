#include "headers/Player.h"
#include "headers/PrimitiveRenderer.h"
#include <iostream>

Player::Player() : speed(2.0f) {
    if (!jumpBuffer.loadFromFile("../../../../assets/brackeys_platformer_assets/sounds/jump.wav")) {
        std::cout << "Blad wczytywania dzwieku jump.wav\n";
    }
    else {
        jumpSound.emplace(jumpBuffer);
        jumpSound->setVolume(50.f);
    }
}

void Player::update() {
    handleInput();
    velocityY -= gravity;

    float nextY = position.y - velocityY;

    if (checkCollision(map, position.x, (int)nextY)) {
        if (velocityY < 0) {
            isJumping = false;
            int tileSize = 48;
            position.y = (int(nextY / tileSize)) * tileSize;
        }
        velocityY = 0;
    }
    else {
        position.y = nextY;
    }
}

void Player::handleInput() {
    bool jumpKeyHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (jumpKeyHeld && !isJumping) {
        velocityY = jumpStrength;
        isJumping = true;

        if (jumpSound) jumpSound->play();
    }

    if (!jumpKeyHeld && isJumping && velocityY > 0.0f) {
        velocityY *= 0.4f;
    }

    //if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isJumping) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !isJumping)) {
    //    velocityY += jumpStrength;
    //    isJumping = true;
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    //    velocityX -= speed;
    //}
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    //    velocityX += speed;
    //}
}

bool Player::checkCollision(std::vector<std::vector<int>>& map, int nextX, int nextY) {
    Rect playerRect = getRect(nextX, nextY);
    int tileSize = 48;

    int left = (playerRect.start.x + mapOffsetX) / tileSize;
    int right = (playerRect.start.x + playerRect.width + mapOffsetX) / tileSize;
    int top = playerRect.start.y / tileSize;
    int bottom = (playerRect.start.y + playerRect.height) / tileSize;

    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
            if (y < 0 || y >= map.size() || x < 0 || x >= map[0].size())
                continue;

            if (map[y][x] == 1 || map[y][x] == 2)
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