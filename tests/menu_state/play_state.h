#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include "game_state.h"
#include <vector>
#include "game_object.h"

class PlayState : public GameState {
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const {
        return s_playID;
    }

private:
    static const std::string s_playID;

    std::vector<GameObject *> m_gameObjects;
};

#endif /* _PLAY_STATE_H_ */
