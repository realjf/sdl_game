#include "tile_layer.h"
#include "game.h"
#include "texture_manager.h"
#include <cmath>

TileLayer::TileLayer(int tileSize, int tileCount, const std::vector<Tileset> &tilesets) : m_numColumns(0),
                                                                                          m_numRows(0),
                                                                                          m_tileSize(tileSize),
                                                                                          m_scale(1.0f),
                                                                                          m_tileCount(tileCount),
                                                                                          m_position(0, 0),
                                                                                          m_velocity(0, 0),
                                                                                          m_tilesets(tilesets) {
    m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize);
    m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
    std::vector<std::vector<int>> tileIDs(m_numRows, std::vector<int>(m_numColumns));
    m_tileIDs = tileIDs;
}

void TileLayer::update() {
    m_position += m_velocity;
    // scrolling a tile map
    m_velocity.setX(1);
}

void TileLayer::render() {
    int x, y, x2, y2 = 0;
    x = ceil(m_position.getX() / m_tileSize);
    y = ceil(m_position.getY() / m_tileSize);
    x2 = int(ceil(m_position.getX())) % m_tileSize;
    y2 = int(ceil(m_position.getY())) % m_tileSize;

    m_scale = TheGame::Instance()->getGameWidth() / TheGame::Instance()->getGameHeight();

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];
            if (id <= 0) {
                continue;
            }
            std::cout << "id ================== " << id << std::endl;
            Tileset tileset = getTilesetByID(id);

            if (id > tileset.count) {
                continue;
            }
            id--;
            std::cout << "count ================== " << tileset.count << std::endl;
            TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, m_tileSize, m_scale, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::Instance()->getRenderer());
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID) {
    int size = m_tilesets.size();
    for (int i = 0; i < size; i++) {
        if (i + 1 <= size - 1) {
            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }

    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t;
    return t;
}
