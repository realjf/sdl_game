#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "texture_manager.h"
#include "player.h"
#include "enemy.h"

class Game {
   private:
    Game() = default;

   public:
    ~Game() = default;

    static Game* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }

    SDL_Renderer* getRenderer() const { return m_pRenderer; }

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void draw();
    void quit();

    bool running() { return m_bRunning; }

   private:
    static Game* s_pInstance;
    bool m_bRunning;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_currentFrame;

    std::vector<GameObject*> m_gameObjects;
};

typedef Game TheGame;

#endif /* _GAME_H_ */
