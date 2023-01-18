#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>
#include "game_object.h"

class Enemy : public GameObject {
   public:
    void load(int x, int y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();
};

#endif /* _ENEMY_H_ */
