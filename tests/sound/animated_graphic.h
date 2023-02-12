#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include "sdl_game_object.h"
#include <SDL.h>
#include "game_object_factory.h"

class AnimatedGraphic : public SDLGameObject {
public:
    AnimatedGraphic();

    void update();
    void draw();
    void clean();
    void load(std::unique_ptr<LoaderParams> const &pParams);
};

class AnimatedGraphicCreator : public BaseCreator {
public:
    GameObject *createGameObject() const override {
        return new AnimatedGraphic();
    }
};

#endif /* _ANIMATED_GRAPHIC_H_ */
