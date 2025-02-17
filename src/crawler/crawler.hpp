#pragma once

#include <vector>
#include <string>

#include "sprite/sprite.hpp"

namespace libgreta{

enum{
    MISSING_UNKNOWN_ASSET = 0,
    MISSING_SPRITE = 1,
    MISSING_SPRITE_TEXTURE = 2,
    MISSING_SPRITE_SOUND = 3,
    MISSING_TILESET = 4,
    MISSING_TILESET_BG = 5,
    MISSING_SCENERY = 6,
    MISSING_LUA = 7
};

enum{    
    REQUIRED_FROM_UNKNOWN_SOURCE = 0,
    REQUIRED_FROM_LEVEL = 1,
    REQUIRED_AMMO1 = 2,
    REQUIRED_AMMO2 = 3,
    REQUIRED_BONUS = 4,
    REQUIRED_TRANSFORMATION = 5,
    REQUIRED_FROM_LUA = 6
};

class GRETA_API MissingAsset{
public:
    MissingAsset() = default;
    MissingAsset(const std::string& name, int type, int requiredFrom, void* parent, std::string msg=""):
    name(name), type(type), requiredFrom(requiredFrom), parent(parent), message(msg){

    }

    std::string name;

    int type = MISSING_SPRITE;
    int requiredFrom = REQUIRED_FROM_UNKNOWN_SOURCE;
    void*parent = nullptr;
    bool malformed = false;

    std::string message;
};


class GRETA_API SpriteNode{
public:
    SpriteNode()=default;
    SpriteNode(const std::string& filename, const SpritePrototype& proto):
    filename(filename), prototype(proto)
    {

    }
    std::string filename;
    SpritePrototype prototype;    
    SpriteNode* transformation     = nullptr;
    SpriteNode* bonus      = nullptr;
    SpriteNode* ammo1     = nullptr;
    SpriteNode* ammo2     = nullptr;
};

class GRETA_API PK2Crawler{
public:
    PK2Crawler()=default;
    bool verbose = false;

    SpriteNode* loadSpriteRecursive(const std::string& name, int requiredFrom, void*parent);

    SpriteNode* loadSprite(const std::string&name){
        return this->loadSpriteRecursive(name, REQUIRED_FROM_UNKNOWN_SOURCE, nullptr);
    }
    
    //DO NOT COPY objects of this class!
    PK2Crawler(const PK2Crawler& src)=delete;
    PK2Crawler& operator=(const PK2Crawler& src) = delete;

    ~PK2Crawler();
private:

    void lookForTexture(SpriteNode* node);
    void lookForSound(SpriteNode*node, const std::string& sound);

    std::vector<std::string> spriteTextures;
    std::vector<std::string> spriteSounds;

    std::vector<SpriteNode*> spriteNodes;
    std::vector<MissingAsset> missingAssets;
};

}