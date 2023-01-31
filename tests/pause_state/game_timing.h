#ifndef _GAME_TIMING_H_
#define _GAME_TIMING_H_

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "game.h"

#define FONT_SIZE 14

class GameTiming {
private:
    GameTiming() = default;

public:
    ~GameTiming() = default;

    static GameTiming *Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new GameTiming();
            return s_pInstance;
        }

        return s_pInstance;
    }

    void startFrameTiming();

    void endFrameTiming();

    void renderText(std::string text, SDL_Rect dest);

private:
    static GameTiming *s_pInstance;

    Uint32 totalFrameTicks = 0;
    Uint32 totalFrames = 0;
    Uint32 startTicks = 0;
    Uint64 startPerf = 0;
    Uint32 endTicks = 0;
    Uint64 endPerf = 0;
    Uint64 framePerf = 0;
};

typedef GameTiming TheGameTiming;

#endif /* _GAME_TIMING_H_ */
