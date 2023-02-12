#include "player.h"
#include "input_handler.h"
#include "game.h"

void Player::draw(RendererFlip flip) {
    if (m_velocity.getX() < 0) {
        ShooterObject::draw(RendererFlip::FLIP_HORIZONTAL);
    } else {
        ShooterObject::draw(RendererFlip::FLIP_NONE);
    }
}

void Player::update() {
    // if the level is complete then fly off the screen
    if (TheGame::Instance()->getLevelComplete()) {
        if (m_position.getX() >= TheGame::Instance()->getGameWidth()) {
            TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
        } else {
            m_velocity.setY(0);
            m_velocity.setX(3);

            //
            m_position += m_velocity;
            m_currentRow = int(SDL_GetTicks() % m_numFrames);

            handleAnimation();
        }
    } else {
        // if the player is not doing its death animation then update it normally
        if (!m_bDying) {
            // reset velocity
            m_velocity.setX(0);
            m_velocity.setY(0);
            // get input
            handleInput();
            // do normal position += velocity update

            //
            m_position += m_velocity;
            m_currentRow = int(SDL_GetTicks() % m_numFrames);

            // update the animation
            handleAnimation();
        } else // if the player is doing the death animation
        {
            m_currentRow = int((SDL_GetTicks() / (100)) % m_numFrames);

            // if the death animation has completed
            if (m_dyingCounter == m_dyingTime) {
                // ressurect the player
                ressurect();
            }
        }
    }
}

void Player::clean() {
    ShooterObject::clean();
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
    ShooterObject::load(std::move(pParams));
}

void Player::collision() {
}

void Player::ressurect() {
    TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;
    m_textureID = "player";
    m_currentFrame = 0;
    m_numFrames = 4;
    m_width = 417;
    m_height = 143;

    m_dyingCounter = 0;
    m_invulnerable = true;
}

void Player::handleInput() {
    Vector2D *target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}

void Player::handleAnimation() {
    // if the player is invulnerable we can flash its alpha to let people know
    if (m_invulnerable) {
        // invulnerability is finished, set values back
        if (m_invulnerableCounter == m_invulnerableTime) {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        } else // otherwise, flash the alpha on and off
        {
            if (m_alpha == 255) {
                m_alpha = 0;
            } else {
                m_alpha = 255;
            }
        }
    }
    // increment our counter
    m_invulnerableCounter++;
    // if the player is not dead then we can change the angle with the velocity to give the impression of a moving helicopter
    if (!m_bDead) {
        if (m_velocity.getX() < 0) {
            m_angle = -10.0;
        } else if (m_velocity.getX() > 0) {
            m_angle = 10.0;
        } else {
            m_angle = 0.0;
        }
    }
    // our standard animation code - for helicopter propellors
    m_currentRow = int((SDL_GetTicks() / (100)) % m_numFrames);
}

Player::Player() : ShooterObject(), m_invulnerable(false), m_invulnerableTime(200), m_invulnerableCounter(0) {
}
