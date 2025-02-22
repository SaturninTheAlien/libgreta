#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "episode_fs.hpp"
#include "sprite/sprite.hpp"
#include "level/level.hpp"

namespace libgreta{

enum{
    ASSET_UNKNOWN = 0,
    ASSET_LEVEL = 1,
    ASSET_SPRITE = 2,
    ASSET_SPRITE_TEXTURE = 3,
    ASSET_SPRITE_SOUND = 4,
    ASSET_TILESET = 5,
    ASSET_SCENERY = 6,
    ASSET_LUA = 7,
    ASSET_GFX = 8
};
/**
 * @brief 
 * Tree-like structure
 */
class GRETA_API Node{
public:
    // Do not copy
    Node(const Node& src) = delete;
    Node& operator= (const Node& src) = delete;

    virtual ~Node() = default;
    std::string filename;
    int type = ASSET_UNKNOWN;
    Node* parent = nullptr;

protected:
    Node(const std::string& filename, int type, Node* parent):
        filename(filename), type(type), parent(parent){
    }

    friend class Episode;
};

class GRETA_API MissingAsset: public Node{
public:
    // Do not copy
    MissingAsset(const MissingAsset& src)=delete;
    MissingAsset& operator= (const MissingAsset& src)=delete;

protected:

    MissingAsset(const std::string& name, int type, Node* parent):
    Node(name, type, parent){
    }

    friend class Episode;
};

class GRETA_API MalformedAsset: public Node{

public:
    // Do not copy
    MalformedAsset(const MalformedAsset& src)=delete;
    MalformedAsset& operator= (const MalformedAsset& src)=delete;


    std::string message;
protected:
    MalformedAsset(const std::string& name, int type, Node* parent, std::string msg):
        Node(name, type, parent), message(msg){
    }
    friend class Episode;
};

class GRETA_API SpriteNode: public Node{
public:

    // Do not copy
    SpriteNode(const SpriteNode& src)=delete;
    SpriteNode& operator= (const SpriteNode& src)=delete;

    SpritePrototype prototype;    
    SpriteNode* transformation     = nullptr;
    SpriteNode* bonus      = nullptr;
    SpriteNode* ammo1     = nullptr;
    SpriteNode* ammo2     = nullptr;

    Node * texture = nullptr;

protected:
    SpriteNode(const std::string& filename, const SpritePrototype& proto, SpriteNode* parent = nullptr):
    Node(filename, ASSET_SPRITE, parent), prototype(proto){
        
    }
    friend class Episode;
};

class GRETA_API Episode: public EpisodeFS{
public:

    Episode(const std::string& assetsPath,
        const std::string& episodeName):
    EpisodeFS(assetsPath, episodeName){

    }

    Episode(const std::string& assetsPath,
        const std::string& episodeName,
        PZip * zip):
        EpisodeFS(assetsPath, episodeName, zip){
        
    }


    explicit Episode(const EpisodeFS& fs):
    EpisodeFS(fs){

    }

    //DO NOT COPY objects of this class!
    Episode(const Episode& src)=delete;
    Episode& operator=(const Episode& src) = delete;

    ~Episode();


    bool debug = false;

    SpriteNode* loadSpriteRecursive(const std::string& name, Node *parent);

    SpriteNode* loadSprite(const std::string&name){
        return this->loadSpriteRecursive(name, nullptr);
    }


    Node* loadLevel(const File& file);
    void checkLevel(const Level& level, Node* node);    
private:
    Node* lookForAsset(std::string name, const std::string& dir, int type, Node * parent,
    const std::string& color = "\x1B[0m");

    std::vector<Node* > nodes;
};

}