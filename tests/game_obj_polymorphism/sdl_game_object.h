#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include "game_object.h"

class SDLGameObject : public GameObject {
   public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

   protected:
    std::string m_textureID;

    int m_currentFrame;
    int m_currentRow;

    int m_x;
    int m_y;

    int m_width;
    int m_height;
};

#endif /* _SDL_GAME_OBJECT_H_ */
