#include "shooter_object.h"

void ShooterObject::load(std::unique_ptr<LoaderParams> const &pParams) {
}

void ShooterObject::draw() {
    if (m_drawCollision) {
        drawCollisionRect();
    }
}

void ShooterObject::update() {
}

ShooterObject::ShooterObject() {
}

void ShooterObject::doDyingAnimation() {
    // keep scrolling with the map
    scroll(TheGame::Instance()->getScrollSpeed());
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
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
