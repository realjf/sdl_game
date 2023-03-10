#include "game.h"
#include <SDL_ttf.h>
#include "game_timing.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const int WINDOW_WIDTH = 1040; // 26 * 40
const int WINDOW_HEIGHT = 720; // 18 * 40

int main(int argc, char **argv) {
    Uint32 frameStart, frameTime;
    if (!TheGame::Instance()->init("animate", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, false)) {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    std::cout << "game init success!\n";

    while (TheGame::Instance()->running()) {

        // Start frame timing
        TheGameTiming::Instance()->startFrameTiming();

        frameStart = SDL_GetTicks();

        SDL_RenderClear(TheGame::Instance()->getRenderer());

        // event loop
        TheGame::Instance()->handleEvents();
        // physics loop
        TheGame::Instance()->update();
        // render loop
        TheGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime)); // add the delay
        }

        // End frame timing
        TheGameTiming::Instance()->endFrameTiming();

        // Display window
        SDL_RenderPresent(TheGame::Instance()->getRenderer());
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}
