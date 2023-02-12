#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include "shooter_object.h"
#include <SDL.h>
#include "game_object_factory.h"

class AnimatedGraphic : public ShooterObject {
public:
    AnimatedGraphic();

    void update();
    void draw(RendererFlip flip = RendererFlip::FLIP_NONE);
    void clean();
    void load(std::unique_ptr<LoaderParams> const &pParams);
};

class AnimatedGraphicCreator : public BaseCreator {
public:
    GameObject *createGameObject() const {
        return new AnimatedGraphic();
    }
};

#endif /* _ANIMATED_GRAPHIC_H_ */
