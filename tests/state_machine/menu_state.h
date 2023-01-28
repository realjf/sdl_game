#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "game_state.h"

class MenuState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_menuID;
    }

private:
    static const std::string s_menuID;
};

#endif /* _MENU_STATE_H_ */
