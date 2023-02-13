#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include "layer.h"
#include "player.h"
#include "collision_manager.h"

// typedef struct {
//     int firstGridID;
//     int tileWidth;
//     int tileHeight;
//     int spacing;
//     int margin;
//     int width;
//     int height;
//     int numColumns;
//     int count;
//     char name[200];
// } Tileset;

class Tileset {
public:
    Tileset() = default;
    ~Tileset() = default;

public:
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    int count;
    std::string name;
};

class LevelParser;

class Level {
public:
    ~Level();

    void update();
    void render();

    std::vector<Tileset> *getTilesets() {
        return &m_tilesets;
    }

    std::vector<Layer *> *getLayers() {
        return &m_layers;
    }

    std::vector<TileLayer *> *getCollisionLayers() { return &m_collisionLayers; }
    const std::vector<TileLayer *> &getCollidableLayers() { return m_collisionLayers; }

    Player *getPlayer() { return m_pPlayer; }
    void setPlayer(Player *pPlayer) { m_pPlayer = pPlayer; }

private:
    friend class LevelParser;
    Level();

    Player *m_pPlayer;
    std::vector<Tileset> m_tilesets;
    std::vector<Layer *> m_layers;
    std::vector<TileLayer *> m_collisionLayers;
};

#endif /* _LEVEL_H_ */
