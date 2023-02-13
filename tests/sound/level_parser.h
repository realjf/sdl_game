#ifndef _LEVEL_PARSER_H_
#define _LEVEL_PARSER_H_

#include "tinyxml.h"
#include "tile_layer.h"
#include <string>

class LevelParser {
public:
    Level *parseLevel(const char *levelFile);

private:
    void parseEmbedTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets);
    void parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets, std::vector<TileLayer *> *pCollisionLayers);
    void parseOutsideTilesets(const char *tilesetFile, TiXmlElement *pTileset, std::vector<Tileset> *pTilesets);
    void parseTextures(TiXmlElement *pTextureRoot);
    void parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayers, Level *pLevel);
    std::string getLevelDir() const {
        return m_levelDir;
    }
    std::string extractLevelDir(const char *levelFile);

    int m_tileSize;
    int m_width;
    int m_height;
    int m_tileCount;
    int m_numColumns;
    std::string m_tiledVersion;

    std::string m_levelDir;
};

#endif /* _LEVEL_PARSER_H_ */
