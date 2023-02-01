#include "enemy.h"
#include "math/number.h"

const unsigned int DELAY_MS = 10000000;

void Enemy::draw() {
    SDLGameObject::draw(m_velocity.getX() > 0);
}

void Enemy::update() {

    m_Axis = rand() % 10 - 4;

    if (m_Axis > 0) {
        m_position.setX(m_velocity.getX() + m_position.getX());
    } else {
        m_position.setY(m_velocity.getY() + m_position.getY());
    }

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

    int velocity = rand() % 6 + 1;
    m_bSameSpeed = (rand() % 100 - 20) > 0;
    if (m_bSameSpeed) {
        velocity = (int)(m_velocity.getX());
    }

    bool direction = (rand() % 10000) > 0;
    if (m_position.getY() < 0) {
        m_velocity.setY(ABS(velocity));
    } else if (m_position.getY() > 400) {
        m_velocity.setY(-ABS(velocity));
    } else {
        if (direction) {
            // same direction
            m_velocity.setY(SIGN(m_velocity.getY()) * ABS(velocity));
        } else {
            m_velocity.setY(-SIGN(m_velocity.getY()) * ABS(velocity));
        }
    }

    if (m_position.getX() < 0) {
        m_velocity.setX(ABS(velocity));
    } else if (m_position.getX() > 400) {
        m_velocity.setX(-ABS(velocity));
    } else {
        if (direction) {
            // same direction
            m_velocity.setX(SIGN(m_velocity.getX()) * ABS(velocity));
        } else {
            m_velocity.setX(-SIGN(m_velocity.getX()) * ABS(velocity));
        }
    }
    // SDLGameObject::update();
}

void Enemy::clean() {
}

Enemy::Enemy(const LoaderParams *pParams) : SDLGameObject(pParams) {
    m_velocity = Vector2D(1.0f, 1.0f);
    srand((unsigned int)((unsigned int)time(nullptr) / DELAY_MS));
}
