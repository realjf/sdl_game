#include "input_handler.h"
#include "game.h"

InputHandler *InputHandler::s_pInstance = 0;

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            TheGame::Instance()->quit();
            break;

        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;

        case SDL_KEYDOWN:
            onKeyDown();
            break;

        case SDL_KEYUP:
            onKeyUp();
            break;

        default:
            break;
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

void InputHandler::onKeyDown() {
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event) {
    setMousePosition(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
}

void InputHandler::onMouseButtonDown(SDL_Event &event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        setMouseButtonState(LEFT, true);
        std::cout << "mouse left clicked\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        setMouseButtonState(MIDDLE, true);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        setMouseButtonState(RIGHT, true);
        std::cout << "mouse right clicked\n";
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        setMouseButtonState(LEFT, false);
        std::cout << "mouse left released\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        setMouseButtonState(MIDDLE, false);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        setMouseButtonState(RIGHT, false);
        std::cout << "mouse right released\n";
    }
}
