#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include "game_object.h"
#include "vector_2d.h"

class SDLGameObject : public GameObject {
public:
    SDLGameObject();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void drawCollisionRect();
    virtual void collision() {}
    virtual std::string type() { return "SDLGameObject"; }

    Vector2D getPosition() const { return m_position; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getScale() const { return m_scale; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }
    int getNumFrames() const { return m_numFrames; }
    int getCollision() const { return m_collision; }

protected:
    std::string m_textureID;

    int m_currentFrame;
    int m_currentRow;
    int m_numFrames;
    int m_collision; // draw collision rect

    int m_callbackID;
    int m_animSpeed;

    int m_width;
    int m_height;
    float m_scale;

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
};

#endif /* _SDL_GAME_OBJECT_H_ */
