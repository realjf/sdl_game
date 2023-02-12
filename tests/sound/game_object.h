#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "loader_params.h"
#include <memory>
#include "vector_2d.h"

class GameObject {
public:
    // base class needs virtual destructor
    virtual ~GameObject() {}
    // load from file
    virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
    // draw the object
    virtual void draw() = 0;
    // do update stuff
    virtual void update() = 0;
    // remove anything that needs to be deleted
    virtual void clean() = 0;
    // object has collided, handle accordingly
    virtual void collision() = 0;
    // get the type of the object
    virtual std::string type() = 0;
    // getters for common variables
    Vector2D &getPosition() { return m_position; }
    Vector2D &getVelocity() { return m_velocity; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    float getScale() { return m_scale; }
    int getAnimSpeed() { return m_animSpeed; }
    int getNumFrames() { return m_numFrames; }
    // scroll along with tile map
    void scroll(float scrollSpeed) {
        if (type() != std::string("Player")) // player is never scrolled
        {
            m_position.setX(m_position.getX() - scrollSpeed);
        }
    }
    // is the object currently being updated?
    bool updating() { return m_bUpdating; }
    // is the object dead?
    bool dead() { return m_bDead; }
    // is the object doing a death animation?
    bool dying() { return m_bDying; }
    // set whether to update the object or not
    void setUpdating(bool updating) { m_bUpdating = updating; }

protected:
    // constructor with default initialisation list
    GameObject() : m_position(0, 0),
                   m_velocity(0, 0),
                   m_acceleration(0, 0),
                   m_width(0),
                   m_height(0),
                   m_currentRow(0),
                   m_currentFrame(0),
                   m_numFrames(1),
                   m_animSpeed(0),
                   m_textureID(""),
                   m_bUpdating(false),
                   m_bDead(false),
                   m_bDying(false),
                   m_angle(0),
                   m_alpha(255),
                   m_scale(1.0f) {
    }
    // movement variables
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    // size variables
    int m_width;
    int m_height;
    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    int m_animSpeed;
    std::string m_textureID;
    // common boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;
    // rotation
    double m_angle;
    // blending
    int m_alpha;
    float m_scale;
};

#endif /* _GAME_OBJECT_H_ */
