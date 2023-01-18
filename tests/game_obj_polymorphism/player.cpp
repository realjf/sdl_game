#include "player.h"

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    m_x -= 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Player::clean() {
}

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {
}
