#ifndef _LOADER_PARAMS_H_
#define _LOADER_PARAMS_H_

#include <iostream>

class LoaderParams {
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames = 1, float scale = 1.0f) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames), m_scale(scale) {
    }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getScale() const { return m_scale; }
    int getNumFrames() const { return m_numFrames; }
    std::string getTextureID() const { return m_textureID; }

private:
    std::string m_textureID;
    int m_numFrames;

    int m_x;
    int m_y;

    int m_width;
    int m_height;

    float m_scale;
};

#endif /* _LOADER_PARAMS_H_ */
