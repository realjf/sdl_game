#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include "game_state.h"
#include <mutex>

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

    bool m_isExit = false;
    std::mutex play_mutex;
};

#endif /* _PLAY_STATE_H_ */
