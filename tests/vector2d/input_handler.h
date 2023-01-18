#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <SDL.h>

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

   private:
    InputHandler();
    ~InputHandler();
    static InputHandler* s_pInstance;
};

#endif /* _INPUT_HANDLER_H_ */
