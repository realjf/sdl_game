#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL.h>
#include <vector>
#include <iostream>
#include "vector2d.h"
#include <mutex>

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
public:
    static InputHandler *Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void update();
    void clean();

    // handle keyboard events
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event &event);
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);

    ~InputHandler() = default;

    bool getMouseButtonState(int buttonNumber) {
        std::lock_guard<std::mutex> lk(mouse_mutex);
        return m_mouseButtonStates[buttonNumber];
    }

    void setMouseButtonState(int buttonNumber, bool flag) {
        std::lock_guard<std::mutex> lk(mouse_mutex);
        m_mouseButtonStates[buttonNumber] = flag;
    }

    bool isKeyDown(SDL_Scancode key);

    Vector2D *getMousePosition() {
        std::lock_guard<std::mutex> lk(mouse_mutex);
        return m_mousePosition;
    }

    void setMousePosition(float x, float y) {
        std::lock_guard<std::mutex> lk(mouse_mutex);
        m_mousePosition->setX(x);
        m_mousePosition->setY(y);
    }

private:
    Vector2D *m_mousePosition;

private:
    InputHandler() {
        for (int i = 0; i < 3; i++) {
            m_mouseButtonStates.push_back(false);
        }
    };

    std::vector<bool> m_mouseButtonStates;
    const Uint8 *m_keystates;

    static InputHandler *s_pInstance;
    std::mutex mouse_mutex;
};

typedef InputHandler TheInputHandler;

#endif /* _INPUT_HANDLER_H_ */
