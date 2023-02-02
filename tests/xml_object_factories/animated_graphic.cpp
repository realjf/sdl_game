#include "animated_graphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject() {
}

void AnimatedGraphic::update() {
    std::cout << "AnimatedGraphic update: " << m_animSpeed << "," << m_numFrames << std::endl;
    m_currentFrame = int((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames);
}

void AnimatedGraphic::draw() {
    SDLGameObject::draw(m_velocity.getX() > 0);
}

void AnimatedGraphic::clean() {
    SDLGameObject::clean();
}

void AnimatedGraphic::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
}
