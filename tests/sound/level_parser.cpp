#include "level_parser.h"
#include "texture_manager.h"
#include "game.h"
#include "game_object_factory.h"
#include "tile_layer.h"
#include "base64.h"
#include "zlib.h"
#include <filesystem>
#include "object_layer.h"

Level *LevelParser::parseLevel(const char *levelFile) {
    // create a tinyxml document and load the map(*.tmx)
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    extractLevelDir(levelFile);

    // create the level object
    Level *pLevel = new Level();

    // get the root node
    TiXmlElement *pRoot = levelDocument.RootElement();

    std::cout << "Loading level:\n"
              << "Version: " << pRoot->Attribute("version") << "\n";
    std::cout << "Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
    std::cout << "Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";

    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    TiXmlElement *pProperties = pRoot->FirstChildElement();

    if (pProperties != NULL) {
        // we must parse the textures needed for this level, which have been added to properties
        for (TiXmlElement *e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("property")) {
                parseTextures(e);
            }
        }
    }

    // parse the tilesets
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            if (e->HasAttribute("source") != TIXML_SUCCESS) {
                parseEmbedTilesets(e, pLevel->getTilesets());
            } else {
                std::string tilesetFile = getLevelDir() + "/" + e->Attribute("source");
                parseOutsideTilesets(tilesetFile.c_str(), e, pLevel->getTilesets());
            }
        }
    }

    // parse any object layers
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer") || e->Value() == std::string("objectgroup")) {
            if (e->FirstChildElement()->Value() == std::string("object")) {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            } else if (e->FirstChildElement()->Value() == std::string("data") ||
                       (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data"))) {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseEmbedTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {

    // embed in map
    // first and the tileset to texture manager
    TheTextureManager::Instance()->load(getLevelDir() + "/" + pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());

    // create a tileset object
    Tileset tileset = Tileset();
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

void LevelParser::parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets, std::vector<TileLayer *> *pCollisionLayers) {
    TileLayer *pTileLayer = new TileLayer(m_tileSize, m_tileCount, *pTilesets);

    bool collidable = false;

    // tile data
    std::vector<std::vector<int>> data = {{0}};

    std::string decodedIDs;
    TiXmlElement *pDataNode = NULL;

    for (TiXmlElement *e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("properties")) {
            for (TiXmlElement *property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
                if (property->Value() == std::string("property")) {
                    if (property->Attribute("name") == std::string("collidable")) {
                        collidable = true;
                    }
                }
            }
        }

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
            if (gids[rows * m_width + cols] > 0) {
                data[rows][cols] = gids[rows * m_width + cols];
            } else {
                data[rows][cols] = 0;
            }
        }
    }

    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);

    if (collidable) {
        pCollisionLayers->push_back(pTileLayer);
    }

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
    // Tileset tileset = {0, 0, 0, 0, 0, 0, 0, 0, 0, ""};
    Tileset tileset = Tileset();
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
    m_tileCount = tileset.count;
    pTilesetRoot->Attribute("columns", &tileset.numColumns);
    m_numColumns = tileset.numColumns;
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    pTilesets->push_back(tileset);
}

void LevelParser::parseTextures(TiXmlElement *pTextureRoot) {

    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayers, Level *pLevel) {
    // create an object layer
    ObjectLayer *pObjectLayer = new ObjectLayer();

    for (TiXmlElement *e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        // std::cout << e->Value();
        if (e->Value() == std::string("object")) {
            int x, y, width, height, numFrames, callbackID, animSpeed;
            double scale = 1.0f;
            std::string textureID;
            std::string type;

            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            type = e->Attribute("type");
            GameObject *pGameObject = TheGameObjectFactory::Instance()->create(type);

            // get the property values
            for (TiXmlElement *properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement()) {
                if (properties->Value() == std::string("properties")) {
                    for (TiXmlElement *property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
                        if (property->Value() == std::string("property")) {
                            if (property->Attribute("name") == std::string("numFrames")) {
                                property->Attribute("value", &numFrames);
                            } else if (property->Attribute("name") == std::string("textureHeight")) {
                                property->Attribute("value", &height);
                            } else if (property->Attribute("name") == std::string("textureID")) {
                                textureID = property->Attribute("value");
                            } else if (property->Attribute("name") == std::string("textureWidth")) {
                                property->Attribute("value", &width);
                            } else if (property->Attribute("name") == std::string("callbackID")) {
                                property->Attribute("value", &callbackID);
                            } else if (property->Attribute("name") == std::string("animSpeed")) {
                                property->Attribute("value", &animSpeed);
                            } else if (property->Attribute("name") == std::string("scale")) {
                                property->Attribute("value", &scale);
                            }
                        }
                    }
                }
            }

            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed, scale)));
            if (type == "Player") {
                pLevel->setPlayer(dynamic_cast<Player *>(pGameObject));
            }
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }

    pLayers->push_back(pObjectLayer);
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
