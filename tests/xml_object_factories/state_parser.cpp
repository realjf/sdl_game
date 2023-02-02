#include "state_parser.h"
#include "texture_manager.h"
#include "game.h"
#include "game_object.h"
#include "game_object_factory.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs) {
    // create the XML document
    TiXmlDocument xmlDoc;

    // load the state file
    if (!xmlDoc.LoadFile(stateFile)) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    // get the root element
    TiXmlElement *pRoot = xmlDoc.RootElement();

    // pre declare the states root node
    TiXmlElement *pStateRoot = 0;
    // get this states root node and assign it to pStateRoot
    for (TiXmlElement *e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == stateID) {
            pStateRoot = e;
        }
    }

    // pre declare the texture root
    TiXmlElement *pTextureRoot = 0;

    // get the root of the texture elements
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("TEXTURES")) {
            pTextureRoot = e;
        }
    }

    // now parse the textures
    parseTextures(pTextureRoot, pTextureIDs);

    // pre declare the object root node
    TiXmlElement *pObjectRoot = 0;

    // get the root node and assign it to pObjectRoot
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("OBJECTS")) {
            pObjectRoot = e;
        }
    }

    // now parse the obejcts
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects) {
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        double scale;
        std::string textureID;
        bool collision = false;

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        if (e->HasAttribute("callbackID") == TIXML_NO_ATTRIBUTE) {
            callbackID = 0;
        } else {
            e->Attribute("callbackID", &callbackID);
        }
        if (e->HasAttribute("scale") == TIXML_NO_ATTRIBUTE) {
            scale = 1.0f;
        } else {
            e->Attribute("scale", &scale);
        }
        if (e->HasAttribute("animSpeed") == TIXML_NO_ATTRIBUTE) {
            animSpeed = 0;
        } else {
            e->Attribute("animSpeed", &animSpeed);
        }
        if (e->HasAttribute("collision") == TIXML_SUCCESS) {
            collision = true;
        }

        textureID = e->Attribute("textureID");

        GameObject *pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed, scale, collision));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(TiXmlElement *pStateRoot, std::vector<std::string> *pTextureIDs) {
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);

        TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
    }
}
