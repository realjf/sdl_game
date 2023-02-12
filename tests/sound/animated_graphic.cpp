#include "animated_graphic.h"

AnimatedGraphic::AnimatedGraphic() : SDLGameObject() {
}

void AnimatedGraphic::update() {
    std::cout << "AnimatedGraphic update: " << m_animSpeed << "," << m_numFrames << std::endl;
    m_currentFrame = int((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames);
}

void AnimatedGraphic::draw() {
    SDLGameObject::draw();
}

void AnimatedGraphic::clean() {
    SDLGameObject::clean();
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams) {
    SDLGameObject::load(pParams);
}
