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
   public:
    Game() = default;
    ~Game() = default;

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void draw();

    bool running() { return m_bRunning; }

   private:
    bool m_bRunning;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_currentFrame;

    std::vector<GameObject*> m_gameObjects;
    GameObject* m_go;
    GameObject* m_player;
    GameObject* m_enemy1;
    GameObject* m_enemy2;
    GameObject* m_enemy3;
};

#endif /* _GAME_H_ */
