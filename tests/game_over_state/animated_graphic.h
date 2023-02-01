#ifndef _ANIMATED_GRAPHIC_H_
#define _ANIMATED_GRAPHIC_H_

#include "sdl_game_object.h"
#include <SDL.h>

class AnimatedGraphic : public SDLGameObject {
public:
    AnimatedGraphic(const LoaderParams *pParams, int animSpeed);

    void update();
    void draw();
    void clean();

private:
    int m_animSpeed;
};

#endif /* _ANIMATED_GRAPHIC_H_ */
