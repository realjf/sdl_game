#include "object_layer.h"

void ObjectLayer::update() {
    for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
        std::cout << "xxxxxx" << std::endl;
    }
}

void ObjectLayer::render() {
    for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
