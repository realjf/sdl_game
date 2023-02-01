#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <string>
#include <iostream>
#include <vector>

class GameState {
public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;
};

#endif /* _GAME_STATE_H_ */
