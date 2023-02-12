#include "shooter_object.h"
#include "game.h"
#include "texture_manager.h"

void ShooterObject::load(std::unique_ptr<LoaderParams> const &pParams) {
    // get position
    m_position = Vector2D(pParams->getX(), pParams->getY());

    // get drawing variables
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
    m_scale = pParams->getScale();
    m_animSpeed = pParams->getAnimSpeed();
    m_callbackID = pParams->getCallbackID();

    m_drawCollision = pParams->getCollision();
}

void ShooterObject::draw(RendererFlip flip) {
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_scale, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, RendererFlipToSDLFlip(flip));
    if (m_drawCollision) {
        drawCollisionRect();
    }
}

void ShooterObject::update() {
    // m_position += m_velocity;
    // m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % (m_numFrames > 0 ? m_numFrames : 1));
}

ShooterObject::ShooterObject() : GameObject(),
                                 m_bulletFiringSpeed(0),
                                 m_bulletCounter(0),
                                 m_moveSpeed(0),
                                 m_dyingTime(0),
                                 m_dyingCounter(0),
                                 m_bPlayedDeathSound(false) {
}

void ShooterObject::doDyingAnimation() {
    // keep scrolling with the map
    scroll(TheGame::Instance()->getScrollSpeed());
    m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % (m_numFrames > 0 ? m_numFrames : 1));
    if (m_dyingCounter == m_dyingTime) {
        m_bDead = true;
    }
    m_dyingCounter++; // simple counter, fine with fixed frame rate
}

void ShooterObject::drawCollisionRect() {
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
