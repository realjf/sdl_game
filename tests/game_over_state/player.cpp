#include "player.h"
#include "input_handler.h"

void Player::draw() {
    SDLGameObject::draw(m_velocity.getX() < 0);
}

void Player::update() {
    // if (TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
    //     m_velocity.setX(1);
    // }
    // if (TheInputHandler::Instance()->getMouseButtonState(RIGHT)) {
    //     m_velocity.setX(-1);
    // }

    // Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    // m_velocity = (*vec - m_position) / 100;

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(-2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(-2);
    }

    handleInput();

    // only for helicopter417x143.png
    m_currentFrame = 0;
    // m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    m_currentRow = int(SDL_GetTicks() % m_numFrames) + 1;
    // m_currentRow = 1;
    // m_acceleration.setX(1);
    SDLGameObject::update();
}

void Player::clean() {
}

void Player::handleInput() {
    Vector2D *target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}

Player::Player(const LoaderParams *pParams) : SDLGameObject(pParams) {
}
