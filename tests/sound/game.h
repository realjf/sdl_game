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
#include "main_menu_state.h"
#include "play_state.h"
#include <SDL_ttf.h>

class Game {
private:
    Game();

public:
    ~Game();

    static Game *Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }

    SDL_Renderer *getRenderer() const { return m_pRenderer; }

    TTF_Font *getFont() const { return m_font; }

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

    int getGameWidth() { return m_gameWidth; }
    int getGameHeight() { return m_gameHeight; }

    float getScrollSpeed() {
        return m_scrollSpeed;
    }

    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }

    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }

    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    bool getLevelComplete() { return m_bLevelComplete; }

    int getPlayerLives() { return m_playerLives; }
    void setPlayerLives(int value) { m_playerLives = value; }

    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:
    SDL_Rect m_winRect;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    bool m_bRunning;

    GameStateMachine *m_pGameStateMachine;
    int m_playerLives;
    float m_scrollSpeed;

    bool m_bLevelComplete;

    bool m_bChangingState;

    int m_currentFrame;

    std::vector<GameObject *> m_gameObjects;

    TTF_Font *m_font;

    int m_gameWidth;
    int m_gameHeight;

    int m_currentLevel;
    int m_nextLevel;

    std::vector<std::string> m_levelFiles;

    Game(const Game &);
    Game &operator=(const Game &);

    static Game *s_pInstance;
};

typedef Game TheGame;

#endif /* _GAME_H_ */
