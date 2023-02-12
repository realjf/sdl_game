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
    m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize) + 1;
    m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
    std::vector<std::vector<int>> tileIDs(m_numRows, std::vector<int>(m_numColumns));
    m_tileIDs = tileIDs;
    m_scale = TheGame::Instance()->getGameWidth() / TheGame::Instance()->getGameHeight();
    m_x = TheGame::Instance()->getGameWidth();
    m_deep.store(0);
    m_nextDeep.store(0);
}

void TileLayer::update() {
    // scrolling a tile map
    // m_position += m_velocity;
    // m_velocity.setX(1);
    // m_x++;
    if (m_position.getX() < ((m_mapWidth * m_tileSize) - TheGame::Instance()->getGameWidth()) - m_tileSize) {
        m_velocity.setX(TheGame::Instance()->getScrollSpeed());
        m_position += m_velocity;

    } else {
        m_velocity.setX(0);
    }
}

void TileLayer::render() {
    int x, y, x2, y2 = 0;
    x = m_position.getX() / m_tileSize;
    y = m_position.getY() / m_tileSize;
    x2 = int(m_position.getX()) % m_tileSize;
    y2 = int(m_position.getY()) % m_tileSize;

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i + y][j + x];

            if (id <= 0) {
                continue;
            }
            Tileset tileset = getTilesetByID(id);

            if (id > tileset.count) {
                continue;
            }
            id--;
            int xx = (j * m_tileSize) - x2;
            int yy = (i * m_tileSize) - y2;
            if (((j + x) * m_tileSize) / TheGame::Instance()->getGameWidth() <= m_deep) {
                yy += (m_deep * m_tileSize);
            } else if (((j + x) * m_tileSize) / TheGame::Instance()->getGameWidth() <= (m_nextDeep + 1)) {
                yy += (m_nextDeep * m_tileSize);
            } else {
                yy += (m_deep * m_tileSize);
            }
            TheTextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, xx, yy, m_tileSize, m_tileSize, m_scale, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns, TheGame::Instance()->getRenderer());
        }
    }
    int x_width = (m_x) / TheGame::Instance()->getGameWidth();
    if (x_width >= m_nextDeep + 1) {
        m_deep.store(m_nextDeep);
    }

    if (x_width > m_nextDeep) {
        m_nextDeep.store(m_nextDeep + 1);
    }
    // std::cout << "deep: " << m_deep << std::endl;
    // std::cout << "next: " << m_nextDeep << std::endl;
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
