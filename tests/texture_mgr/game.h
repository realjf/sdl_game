#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "texture_manager.h"

class Game {
   public:
    Game() = default;
    ~Game() = default;

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() { return m_bRunning; }

   private:
    bool m_bRunning;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_currentFrame;
    TextureManager m_textureManager;
};

#endif /* _GAME_H_ */
