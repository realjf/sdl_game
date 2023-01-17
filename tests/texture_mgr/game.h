#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

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
    SDL_Texture* m_pTextureFlip;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
    SDL_Rect m_destinationRectangleFlip;
    int startFrame;
    int frameLoop;
};

#endif /* _GAME_H_ */
