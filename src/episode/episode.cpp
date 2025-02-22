#include "episode.hpp"
#include "utils/string_utils.hpp"
#include "sprite/sprite_io.hpp"
#include "level/level_io.hpp"

#include <sstream>
#include <iostream>


namespace libgreta{

std::string Asset::str()const{
    return this->filename;
}


std::string Asset::getStackTrace()const{
    std::ostringstream os;

    int i = 0;
    const Asset* child = nullptr;
    
    for(const Asset* asset = this; asset!=nullptr; asset = asset->parent){
        os<<"["<<i<<"] "<<asset->str();

        const SpriteAsset* sprite = dynamic_cast<const SpriteAsset*>(asset);
        if(sprite!=nullptr && child!=nullptr){
            if(sprite->ammo1 == child){
                os << " (ammo1)";
            }
            if(sprite->ammo2 == child){
                os << " (ammo2)";
            }
            if(sprite->bonus == child){
                os << " (bonus)";
            }
            if(sprite->transformation == child){
                os << " (transformation)";
            }
            if(sprite->texture == child){
                os << " (texture)";
            }
        }

        os << std::endl;
        ++i;
        child = asset;
    }

    return os.str();
}

std::string MissingAsset::str()const{
    return std::string("(missing!) ") + this->filename;
} 

std::string MalformedAsset::str()const{
    return std::string("(malformed!) ")+ this->filename;
}


std::string SpriteAsset::str()const{
    std::string s = PString::removeSuffix(this->filename, ".spr2");
    return std::string("(sprite) ")+ s + "[.spr2/.spr]";
}

Episode::~Episode(){
    for(Asset*& proto:this->assets){
        if(proto!=nullptr){
            delete proto;
            proto = nullptr;
        }
    }

    this->assets.clear();
}

Asset* Episode::loadLevel(const File& file){

    if(this->debug){
        std::cout<<"Loading level: \x1B[93m\""<<file.getFilename()<<"\"\x1B[0m"<<std::endl;
    }

    try{
        Level level = LoadLevel(file);
        Asset * levelAsset = new Asset(file.getFilename(), ASSET_LEVEL, nullptr);
        this->assets.emplace_back(levelAsset);
        this->checkLevel(level, levelAsset);
        return levelAsset;
    }
    catch(const std::exception& e){
        MalformedAsset* malformedLevel = new MalformedAsset(
            file.getFilename(),
            ASSET_LEVEL,
            nullptr,
            e.what());

        this->assets.emplace_back(malformedLevel);
        return malformedLevel;
    }

    return nullptr;
}

void Episode::checkLevel(const Level& level, Asset * levelAsset){

    //Lua
    this->lookForAsset(level.lua_script,
        LUA_DIR,
        ASSET_LUA,
        levelAsset,
        "\x1B[94m");

    for(const LevelSector* sector: level.sectors){

        //BG
        this->lookForAsset(sector->backgroundName,
            SCENERY_DIR,
            ASSET_SCENERY,
            levelAsset,
            "\x1B[92m");

        //Tileset FG
        this->lookForAsset(sector->tilesetName,
            TILES_DIR,
            ASSET_TILESET,
            levelAsset,
            "\x1B[92m");

        //Tileset BG
        this->lookForAsset(sector->bgTilesetName,
            TILES_DIR,
            ASSET_TILESET,
            levelAsset,
            "\x1B[92m");

        //GFX texture
        this->lookForAsset(sector->gfxTextureName,
            GFX_DIR,
            ASSET_GFX,
            levelAsset,
            "\x1B[92m");
    }

    //Sprites
    for(const std::string& spriteName: level.spritesList){
        this->loadSpriteRecursive(spriteName, levelAsset);
    }
}

Asset* Episode::loadSpriteRecursive(const std::string& name,Asset *parent){
    try{
        if(name.empty()){
            return nullptr;
        }


        std::string name1 = PString::rtrim(PString::lowercase(name));
        
        //require .spr2 at first, if not found require .spr
        if(PString::endsWith(name1, ".spr")){
            name1+="2";
        }

        //check if already loaded
        for(Asset * node: this->assets){
            if(node->filename==name1 && node->type == ASSET_SPRITE){
                return node;
            }
        }

        if(this->debug){
            std::cout<<"Looking for: "<< "\x1B[32m\""<<name1<<"/.spr\"\x1B[0m"<<std::endl;
        }

        std::optional<File> file = this->findAsset(name1, SPRITES_DIR, ".spr");
        if(!file.has_value()){

            if(this->debug){
                std::cout<<"\x1B[31mSprite: \"" << name1<<"\" not found!\x1B[0m"<<std::endl;
            }
            Asset* missing = new MissingAsset(name, ASSET_SPRITE, parent);
            this->assets.emplace_back(missing);

            return missing;
        }

        SpriteAsset* spriteNode = new SpriteAsset(name1, LoadSprite(*file), parent);
        this->assets.emplace_back(spriteNode);

        const SpritePrototype& proto = spriteNode->prototype;

        //texture
        spriteNode->texture =  this->lookForAsset(
            spriteNode->prototype.picture_filename,
            SPRITES_DIR,
            ASSET_SPRITE_TEXTURE, 
            spriteNode,
            "\x1B[36m");
        
        //sounds
        for(const std::string& soundName: proto.sounds){

            this->lookForAsset(
                soundName,
                SPRITES_DIR,
                ASSET_SPRITE_SOUND,
                spriteNode,
                "\x1B[34m");
        }

        //bonus
        spriteNode->bonus = this->loadSpriteRecursive(proto.bonus_str, spriteNode);

        //ammo1
        spriteNode->ammo1 = this->loadSpriteRecursive(proto.ammo1_str, spriteNode);

        //ammo2
        spriteNode->ammo2 = this->loadSpriteRecursive(proto.ammo2_str, spriteNode);

        //transformation
        spriteNode->transformation = this->loadSpriteRecursive(proto.transformation_str, spriteNode);

        return spriteNode;

    }
    catch(const std::exception& e){

        MalformedAsset * malformed = new MalformedAsset(name, ASSET_SPRITE, parent, e.what());
        this->assets.emplace_back(malformed);
        return malformed;
    }

    return nullptr;
}

Asset* Episode::lookForAsset(std::string name, const std::string& dir, int assetType, Asset * parent,
        const std::string& color){
    //

    if(name.empty())return nullptr;
    
    name = PString::rtrim(PString::lowercase(name));
    for(Asset * node:this->assets){
        if(node->type == assetType && node->filename == name){
            return node;
        }
    }

    if(this->debug){
        std::cout<< "Looking for: "<<color<<"\""<<name<<"\"\x1B[0m"<<std::endl;
    }

    Asset* result = nullptr;

    std::optional<File> file = this->findAsset(name, dir, "");
    if(!file.has_value()){
        if(this->debug){
            std::cout<<"\x1B[31mFile: \""<<name<<"\" not found!\x1B[0m"<<std::endl;
        }
        result = new MissingAsset(name, assetType, parent);
    }
    else{
        result = new Asset(name, assetType, parent);
    }

    this->assets.emplace_back(result);
    return result;
}

std::vector<MissingAsset*> Episode::getMissingAssets(){
    std::vector<MissingAsset*>result;
    for(Asset * asset: this->assets){
        MissingAsset * missingAsset = dynamic_cast<MissingAsset*>(asset);
        if(missingAsset!=nullptr){
            result.emplace_back(missingAsset);
        }
    }
    return result;
}

std::vector<MalformedAsset*> Episode::getMalformedAssets(){
    std::vector<MalformedAsset*>result;
    for(Asset * asset: this->assets){
        MalformedAsset * missingAsset = dynamic_cast<MalformedAsset*>(asset);
        if(missingAsset!=nullptr){
            result.emplace_back(missingAsset);
        }
    }
    return result;
}

}