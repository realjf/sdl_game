#include "game_timing.h"

GameTiming *GameTiming::s_pInstance = 0;

void GameTiming::startFrameTiming() {
    // Start frame timing
    totalFrames++;
    startTicks = SDL_GetTicks();
    startPerf = SDL_GetPerformanceCounter();
}

void GameTiming::endFrameTiming() {
    // End frame timing
    endTicks = SDL_GetTicks();
    endPerf = SDL_GetPerformanceCounter();
    framePerf = endPerf - startPerf;
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
}

void GameTiming::renderText(std::string text, SDL_Rect dest) {
    SDL_Color fg = {0, 0, 0};
    SDL_Surface *surf = TTF_RenderText_Solid(TheGame::Instance()->getFont(), text.c_str(), fg);

    dest.w = surf->w;
    dest.h = surf->h;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), surf);

    SDL_RenderCopy(TheGame::Instance()->getRenderer(), tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}
