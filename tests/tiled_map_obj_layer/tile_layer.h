#ifndef _TILE_LAYER_H_
#define _TILE_LAYER_H_

#include "vector_2d.h"
#include <vector>
#include "level.h"
#include <atomic>

class TileLayer : public Layer {
public:
    TileLayer(int tileSize, int tileCount, const std::vector<Tileset> &tilesets);

    virtual void update();
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int>> &data) {
        m_tileIDs = data;
    }

    void setTileSize(int tileSize) {
        m_tileSize = tileSize;
    }

    void setScale(float scale) {
        m_scale = scale;
    }

    Tileset getTilesetByID(int tileID);

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;
    float m_scale = 1.0f;
    int m_tileCount;
    std::atomic<int> m_deep;
    std::atomic<int> m_nextDeep;
    int m_x = 0;

    Vector2D m_position;
    Vector2D m_velocity;

    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int>> m_tileIDs;
};

#endif /* _TILE_LAYER_H_ */
