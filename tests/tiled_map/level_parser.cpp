#include "level_parser.h"
#include "texture_manager.h"
#include "game.h"
#include "game_object_factory.h"
#include "tile_layer.h"
#include "base64.h"
#include "zlib.h"
#include <filesystem>

Level *LevelParser::parseLevel(const char *levelFile) {
    // create a tinyxml document and load the map(*.tmx)
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    extractLevelDir(levelFile);

    // create the level object
    Level *pLevel = new Level();

    // get the root node
    TiXmlElement *pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);
    m_tiledVersion = pRoot->Attribute("tiledversion");

    // parse the tilesets
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            if (e->FirstChildElement() != NULL) {
                parseEmbedTilesets(e, pLevel->getTilesets());
            } else {
                std::string tilesetFile = getLevelDir() + "/" + e->Attribute("source");
                parseOutsideTilesets(tilesetFile.c_str(), e, pLevel->getTilesets());
            }
        }
    }

    // parse any object layers
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
        }
    }

    return pLevel;
}

void LevelParser::parseEmbedTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {

    // embed in map
    // first and the tileset to texture manager
    TheTextureManager::Instance()->load(getLevelDir() + "/" + pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    if (pTilesetRoot->HasAttribute("spacing") == TIXML_SUCCESS) {
        pTilesetRoot->Attribute("spacing", &tileset.spacing);
    } else {
        tileset.spacing = 0;
    }
    if (pTilesetRoot->HasAttribute("margin") == TIXML_SUCCESS) {
        pTilesetRoot->Attribute("margin", &tileset.margin);
    } else {
        tileset.margin = 0;
    }
    pTilesetRoot->Attribute("tilecount", &tileset.count);
    pTilesetRoot->Attribute("columns", &tileset.numColumns);
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets) {
    TileLayer *pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement *pDataNode;

    for (TiXmlElement *e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }

    for (TiXmlNode *e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        TiXmlText *text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef *)&gids[0], &numGids, (const Bytef *)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);

    for (int j = 0; j < m_height; j++) {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++) {
        for (int cols = 0; cols < m_width; cols++) {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void LevelParser::parseOutsideTilesets(const char *tilesetFile, TiXmlElement *pTileset, std::vector<Tileset> *pTilesets) {
    // outside the map
    // create a tinyxml document and load the map(*.tmx)
    TiXmlDocument tsxDocument;
    tsxDocument.LoadFile(tilesetFile);

    // get the root node
    TiXmlElement *pTilesetRoot = tsxDocument.RootElement();

    // first and the tileset to texture manager
    std::string tilesetImage = getLevelDir() + "/" + pTilesetRoot->FirstChildElement()->Attribute("source");
    TheTextureManager::Instance()->load(tilesetImage, pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    if (pTilesetRoot->HasAttribute("spacing") == TIXML_SUCCESS) {
        pTilesetRoot->Attribute("spacing", &tileset.spacing);
    } else {
        tileset.spacing = 0;
    }
    if (pTilesetRoot->HasAttribute("margin") == TIXML_SUCCESS) {
        pTilesetRoot->Attribute("margin", &tileset.margin);
    } else {
        tileset.margin = 0;
    }

    pTilesetRoot->Attribute("tilecount", &tileset.count);
    pTilesetRoot->Attribute("columns", &tileset.numColumns);
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

std::string LevelParser::extractLevelDir(const char *levelFile) {
    std::string path(levelFile);
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    static const std::string slash = "\\";
#else
    static const std::string slash = "/";
#endif
    const size_t lastSlashIdx = path.rfind(slash);
    if (std::string::npos != lastSlashIdx) {
        m_levelDir = path.substr(0, lastSlashIdx);
    }

    return path.substr(0, lastSlashIdx);
}
