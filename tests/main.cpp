#include <SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderder = 0;

int main(int argc, char* args[]) {
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        // if successed create our window
        g_pWindow = SDL_CreateWindow("sdl game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
        // if the window creation succeeded create our renderer
        if (g_pWindow != 0) {
            g_pRenderder = SDL_CreateRenderer(g_pWindow, -1, 0);
        }
    } else {
        return 1;  // sdl could not initialize
    }
    // everything succeeded lets draw the window set to black
    // This function expects Red, Green, Blue and Alpha as color values
    SDL_SetRenderDrawColor(g_pRenderder, 0, 0, 0, 255);

    // clear the window to black
    SDL_RenderClear(g_pRenderder);

    // show the window
    SDL_RenderPresent(g_pRenderder);

    // set a delay before quitting
    SDL_Delay(5000);

    // clean up SDL
    SDL_Quit();

    return 0;
}
