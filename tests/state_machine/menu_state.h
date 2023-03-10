#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include "game_state.h"
#include <vector>
#include "game_object.h"
#include <mutex>

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

    // store menu items
    std::vector<GameObject *> m_gameObjects;
    bool m_isExit = false;
    std::mutex menu_mutex;
};

#endif /* _MENU_STATE_H_ */
