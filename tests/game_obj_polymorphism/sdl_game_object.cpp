#include "sdl_game_object.h"
#include "game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams) {
    m_x = pParams->getX();
    m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentFrame = 1;
    m_currentRow = 1;
}

void SDLGameObject::draw() {
    TheTextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update() {
    m_x += 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void SDLGameObject::clean() {
    std::cout << "clean sdl game object\n";
}
