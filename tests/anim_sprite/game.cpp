#include "game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0) {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            } else {
                std::cout << "renderer init fail\n";
                return false;
            }
        } else {
            std::cout << "window init fail\n";
            return false;
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;

    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/images/anim_sheet_32x64.bmp");
    if (pTempSurface == NULL) {
        std::cout << "load bitmap fail\n";
        return false;
    }
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    m_pTextureFlip = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    m_sourceRectangle.w = 32;
    m_sourceRectangle.h = 64;
    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    startFrame = 5;  // start from sixth frame
    frameLoop = 3;
    m_sourceRectangle.x = m_sourceRectangle.w * startFrame;
    m_sourceRectangle.y = m_sourceRectangle.h;

    m_destinationRectangleFlip.x = m_sourceRectangle.w * 5;
    m_destinationRectangleFlip.y = 0;

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangleFlip.w = m_sourceRectangle.w;
    m_destinationRectangleFlip.h = m_sourceRectangle.h;
    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    // SDL_RenderCopy(m_pRenderer, m_pTexture, 0, 0); // use the entire renderer for display
    // flip image
    SDL_RenderCopyEx(m_pRenderer, m_pTextureFlip, &m_sourceRectangle, &m_destinationRectangleFlip, 0, 0, SDL_FLIP_HORIZONTAL);
    SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
    m_sourceRectangle.x = m_sourceRectangle.w * startFrame + m_sourceRectangle.w * int(((SDL_GetTicks() / 100) % frameLoop));
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_bRunning = false;
                    break;
                }
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean() {
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
