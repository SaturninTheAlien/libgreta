#pragma once

#include <string>
#include <vector>

#include <filesystem>

#include "episode_fs.hpp"
#include "sprite/sprite.hpp"
#include "level/level.hpp"

namespace libgreta{

enum{
    ASSET_EPISODE_ROOT = -1,
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
class GRETA_API Asset{
public:
    // Do not copy
    Asset(const Asset& src) = delete;
    Asset& operator= (const Asset& src) = delete;
    
    virtual ~Asset() = default;
    virtual std::string str()const;

    std::string filename;
    int type = ASSET_UNKNOWN;
    Asset* parent = nullptr;

    std::string getStackTrace()const;

protected:
    Asset(const std::string& filename, int type, Asset* parent):
        filename(filename), type(type), parent(parent){
    }

    friend class EpisodeTree;
};

class GRETA_API MissingAsset: public Asset{
public:
    // Do not copy
    MissingAsset(const MissingAsset& src)=delete;
    MissingAsset& operator= (const MissingAsset& src)=delete;

    virtual std::string str()const;

protected:

    MissingAsset(const std::string& name, int type, Asset* parent):
    Asset(name, type, parent){
    }

    friend class EpisodeTree;
};

class GRETA_API MalformedAsset: public Asset{

public:
    // Do not copy
    MalformedAsset(const MalformedAsset& src)=delete;
    MalformedAsset& operator= (const MalformedAsset& src)=delete;

    virtual std::string str()const;

    std::string what;
protected:
    MalformedAsset(const std::string& name, int type, Asset* parent, std::string msg):
        Asset(name, type, parent), what(msg){
    }
    friend class EpisodeTree;
};

class GRETA_API SpriteAsset: public Asset{
public:

    // Do not copy
    SpriteAsset(const SpriteAsset& src)=delete;
    SpriteAsset& operator= (const SpriteAsset& src)=delete;

    SpritePrototype prototype;    
    Asset* transformation     = nullptr;
    Asset* bonus      = nullptr;
    Asset* ammo1     = nullptr;
    Asset* ammo2     = nullptr;

    Asset * texture = nullptr;

    virtual std::string str()const;
protected:
    SpriteAsset(const std::string& filename, const SpritePrototype& proto, Asset* parent):
    Asset(filename, ASSET_SPRITE, parent), prototype(proto){
        
    }
    friend class EpisodeTree;
};

class GRETA_API EpisodeTree: public EpisodeFS{
public:

    EpisodeTree(const std::string& assetsPath,
        const std::string& episodeName):
    EpisodeFS(assetsPath, episodeName){

    }

    EpisodeTree(const std::string& assetsPath,
        const std::string& episodeName,
        PZip * zip):
        EpisodeFS(assetsPath, episodeName, zip){
        
    }


    explicit EpisodeTree(const EpisodeFS& fs):
    EpisodeFS(fs){

    }

    //DO NOT COPY objects of this class!
    EpisodeTree(const EpisodeTree& src)=delete;
    EpisodeTree& operator=(const EpisodeTree& src) = delete;
    ~EpisodeTree();

    bool debug = false;
    Asset* loadSpriteRecursive(const std::string& name, Asset *parent);
    SpriteAsset* loadSprite(const std::string&name){
        return dynamic_cast<SpriteAsset*>(this->loadSpriteRecursive(name, nullptr));
    }

    std::vector<MissingAsset*> getMissingAssets();
    std::vector<MalformedAsset*> getMalformedAssets();

    //std::string getHealthReport()const;

    Asset* loadLevel(const File& file);
    int loadAllLevels();

private:    
    void checkLevel(const Level& level, Asset* node);

    Asset* lookForAsset(std::string name, const std::string& dir, int type, Asset * parent,
    const std::string& color = "\x1B[0m");

    std::vector<Asset* > assets;
    Asset * episodeRoot = nullptr;

};

}