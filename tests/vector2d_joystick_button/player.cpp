#include "player.h"

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    m_acceleration.setX(1);
    SDLGameObject::update();
}

void Player::clean() {
}

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {
}
