#include "input_handler.h"
#include "game.h"

InputHandler *InputHandler::s_pInstance = 0;

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            TheGame::Instance()->quit();
        }
        m_keystates = SDL_GetKeyboardState(0);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = true;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = true;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = false;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = false;
            }
        }

        if (event.type == SDL_MOUSEMOTION) {
            const SDL_Rect *winRect = TheGame::Instance()->getWindowRect();
            m_mousePosition->setX(event.motion.x);
            m_mousePosition->setY(event.motion.y);
            int x = winRect->x;
            int y = winRect->y;
            int w = winRect->w;
            int h = winRect->h;
            if (x > event.motion.x) {
                m_mousePosition->setX(0);
            }
            if (y > event.motion.y) {
                m_mousePosition->setY(0);
            }
            if (event.motion.x > x + w) {
                m_mousePosition->setX(x + w);
            }
            if (event.motion.y > y + h) {
                m_mousePosition->setY(h + h);
            }
            if (event.motion.x >= x && event.motion.y >= y && event.motion.x <= x + w && event.motion.y <= y + h) {
                m_mousePosition->setX(event.motion.x);
                m_mousePosition->setY(event.motion.y);
            }
        }
    }
}

void InputHandler::clean() {
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        }
    }
    return false;
}
