#include "sdl_game_object.h"
#include "game.h"

SDLGameObject::SDLGameObject() : GameObject() {
}

void SDLGameObject::draw(bool flip) {
    if (flip) {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_scale, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_scale, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
    }
    // TheTextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
    // m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void SDLGameObject::clean() {
    std::cout << "clean sdl game object\n";
}

void SDLGameObject::load(const LoaderParams *pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0, 0);
    m_acceleration = Vector2D(0, 0);
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_scale = pParams->getScale();
    m_numFrames = pParams->getNumFrames();
    m_textureID = pParams->getTextureID();

    m_currentFrame = 1;
    m_currentRow = 1;
}
