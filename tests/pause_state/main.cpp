#include "game.h"
#include <SDL_ttf.h>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

void renderText(std::string text, SDL_Rect dest);

int main(int argc, char **argv) {
    Uint32 frameStart, frameTime;
    if (!TheGame::Instance()->init("animate", 100, 100, 640, 480, false)) {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    std::cout << "game init success!\n";

    Uint32 totalFrameTicks = 0;
    Uint32 totalFrames = 0;
    while (TheGame::Instance()->running()) {

        // Start frame timing
        totalFrames++;
        Uint32 startTicks = SDL_GetTicks();
        Uint64 startPerf = SDL_GetPerformanceCounter();

        SDL_RenderClear(TheGame::Instance()->getRenderer());

        frameStart = SDL_GetTicks();

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime)); // add the delay
        }

        // End frame timing
        Uint32 endTicks = SDL_GetTicks();
        Uint64 endPerf = SDL_GetPerformanceCounter();
        Uint64 framePerf = endPerf - startPerf;
        float frameTime = (endTicks - startTicks) / 1000.0f;
        totalFrameTicks += endTicks - startTicks;

        // Strings to display
        std::string fps = "Current FPS: " + std::to_string(1.0f / frameTime);
        std::string avg = "Average FPS: " + std::to_string(1000.0f / ((float)totalFrameTicks / totalFrames));
        std::string perf = "Current Perf: " + std::to_string(framePerf);

        // Display strings
        SDL_Rect dest;
        dest.x = dest.y = 0;
        dest.w = dest.h = 10;
        renderText(fps, dest);
        dest.y += 24;
        renderText(avg, dest);
        dest.y += 24;
        renderText(perf, dest);

        // Display window
        SDL_RenderPresent(TheGame::Instance()->getRenderer());
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}

void renderText(std::string text, SDL_Rect dest) {
    SDL_Color fg = {0, 0, 0};
    SDL_Surface *surf = TTF_RenderText_Solid(TheGame::Instance()->getFont(), text.c_str(), fg);

    dest.w = surf->w;
    dest.h = surf->h;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surf);

    SDL_RenderCopy(TheGame::Instance()->getRenderer(), tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}
