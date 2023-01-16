#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <iostream>

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

    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
};

#endif /* _GAME_H_ */
