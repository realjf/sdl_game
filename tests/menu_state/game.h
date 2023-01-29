#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "texture_manager.h"
#include "player.h"
#include "enemy.h"
#include "game_state_machine.h"
#include "menu_state.h"
#include "play_state.h"

class Game {
private:
    Game() = default;

public:
    ~Game() = default;

    static Game *Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }

    SDL_Renderer *getRenderer() const { return m_pRenderer; }

    bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void draw();
    void quit();
    SDL_Rect getWindowRect() {
        SDL_GetWindowSize(m_pWindow, &m_winRect.w, &m_winRect.h);
        SDL_GetWindowPosition(m_pWindow, &m_winRect.x, &m_winRect.y);

        return m_winRect;
    }

    bool running() { return m_bRunning; }

    GameStateMachine *getStateMachine() {
        return m_pGameStateMachine;
    }

private:
    static Game *s_pInstance;
    bool m_bRunning;
    SDL_Rect m_winRect;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    int m_currentFrame;

    std::vector<GameObject *> m_gameObjects;

    GameStateMachine *m_pGameStateMachine;
};

typedef Game TheGame;

#endif /* _GAME_H_ */
