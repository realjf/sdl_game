#include "player.h"
#include "input_handler.h"

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
        m_velocity.setX(1);
    }
    if (TheInputHandler::Instance()->getMouseButtonState(RIGHT)) {
        m_velocity.setX(-1);
    }
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    // m_acceleration.setX(1);
    SDLGameObject::update();
}

void Player::clean() {
}

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {
}
