#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL.h>
#include <vector>
#include <iostream>
#include "math/vector2d.h"

enum mouse_buttons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
   public:
    static InputHandler* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void update();
    void clean();

    ~InputHandler() = default;

    bool getMouseButtonState(int buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }

    bool isKeyDown(SDL_Scancode key);

    Vector2D* getMousePosition() {
        return m_mousePosition;
    }

   private:
    Vector2D* m_mousePosition;

   private:
    InputHandler() {
        for (int i = 0; i < 3; i++) {
            m_mouseButtonStates.push_back(false);
        }
    };

    std::vector<bool> m_mouseButtonStates;
    const Uint8* m_keystates;

    static InputHandler* s_pInstance;
};

typedef InputHandler TheInputHandler;

#endif /* _INPUT_HANDLER_H_ */
