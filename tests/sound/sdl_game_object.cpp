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
    if (m_collision) {
        drawCollisionRect();
    }
}

void SDLGameObject::update() {
    // m_velocity += m_acceleration;
    // m_position += m_velocity;
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
    m_animSpeed = pParams->getAnimSpeed();
    m_callbackID = pParams->getCallbackID();
    m_collision = pParams->getCollision();

    m_currentFrame = 1;
    m_currentRow = 1;
}

void SDLGameObject::drawCollisionRect() {
    SDL_Rect *rect = new SDL_Rect();

    // collision sides
    rect->x = m_position.getX();
    rect->w = m_width * m_scale;
    rect->y = m_position.getY();
    rect->h = m_height * m_scale;

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(TheGame::Instance()->getRenderer(), &r, &g, &b, &a);
    SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 255, 0, 255);
    SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), rect);
    SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), r, g, b, a);
}
