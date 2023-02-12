#ifndef _OBJECT_LAYER_H_
#define _OBJECT_LAYER_H_

#include "layer.h"
#include "game_object.h"

class ObjectLayer : public Layer {
public:
    virtual void update();
    virtual void render();

    std::vector<GameObject *> *getGameObjects() {
        return &m_gameObjects;
    }

private:
    std::vector<GameObject *> m_gameObjects;
};

#endif /* _OBJECT_LAYER_H_ */
