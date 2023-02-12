#ifndef _LOADER_PARAMS_H_
#define _LOADER_PARAMS_H_

#include <iostream>

class LoaderParams {
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0, float scale = 1.0f, bool collision = false) : m_textureID(textureID),
                                                                                                                                                                                 m_x(x),
                                                                                                                                                                                 m_y(y),
                                                                                                                                                                                 m_width(width),
                                                                                                                                                                                 m_height(height),

                                                                                                                                                                                 m_numFrames(numFrames),
                                                                                                                                                                                 m_callbackID(callbackID),
                                                                                                                                                                                 m_animSpeed(animSpeed),
                                                                                                                                                                                 m_scale(scale),
                                                                                                                                                                                 m_collision(collision) {
        if (!(m_callbackID > 0)) {
            m_callbackID = 0;
        }
        if (!(m_animSpeed > 0)) {
            m_animSpeed = 0;
        }
        if (!(m_scale > 0.0f)) {
            m_scale = 1.0f;
        }
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getScale() const { return m_scale; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }
    int getCollision() const { return m_collision; }
    std::string getTextureID() const { return m_textureID; }

private:
    std::string m_textureID;
    int m_x;
    int m_y;

    int m_width;
    int m_height;
    int m_numFrames;
    int m_callbackID;
    int m_animSpeed;
    float m_scale;
    int m_collision;
};

#endif /* _LOADER_PARAMS_H_ */
