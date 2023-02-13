#ifndef _OBJECT_LAYER_H_
#define _OBJECT_LAYER_H_

#include "layer.h"
#include "game_object.h"
#include "level.h"
#include "collision_manager.h"

class ObjectLayer : public Layer {
public:
    virtual ~ObjectLayer();

    virtual void update(Level *pLevel);
    virtual void render();

    std::vector<GameObject *> *getGameObjects() {
        return &m_gameObjects;
    }

private:
    // check for collisions between game objects
    CollisionManager m_collisionManager;

    std::vector<GameObject *> m_gameObjects;
};

#endif /* _OBJECT_LAYER_H_ */
