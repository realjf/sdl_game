#include "level_parser.h"
#include "texture_manager.h"
#include "game.h"
#include "game_object_factory.h"

Level *LevelParser::parseLevel(const char *levelFile) {
    // create a tinyxml document and load the map(*.tmx)
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    // create the level object
    Level *pLevel = new Level();

    // get the root node
    TiXmlElement *pRoot = levelDocument.RootElement();

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // parse the tilesets
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            parseTilesets(e, pLevel->getTilesets());
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

void LevelParser::parseTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {
    // first and the tileset to texture manager
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets) {
}
