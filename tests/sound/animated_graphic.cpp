#include "animated_graphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject() {
}

void AnimatedGraphic::update() {
    std::cout << "AnimatedGraphic update: " << m_animSpeed << "," << m_numFrames << std::endl;
    m_currentFrame = int((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames);
}

void AnimatedGraphic::draw(RendererFlip flip) {
    ShooterObject::draw(flip);
}

void AnimatedGraphic::clean() {
    ShooterObject::clean();
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams) {
    ShooterObject::load(std::move(pParams));
}
