#include "episode.hpp"
#include "utils/string_utils.hpp"
#include "sprite/sprite_io.hpp"
#include "level/level_io.hpp"

#include <iostream>


namespace libgreta{

Episode::~Episode(){
    for(Node*& proto:this->nodes){
        if(proto!=nullptr){
            delete proto;
            proto = nullptr;
        }
    }

    this->nodes.clear();
}

Node* Episode::loadLevel(const File& file){

    Node * levelNode = new Node(file.getFilename(), ASSET_LEVEL, nullptr);

    if(this->debug){
        std::cout<<"Loading level: \x1B[93m\""<<file.getFilename()<<"\"\x1B[0m"<<std::endl;
    }

    this->nodes.emplace_back(levelNode);

    Level level = LoadLevel(file);
    this->checkLevel(level, levelNode);

    return levelNode;
}

void Episode::checkLevel(const Level& level, Node * node){

    //Lua
    this->lookForAsset(level.lua_script,
        LUA_DIR,
        ASSET_LUA,
        node,
        "\x1B[94m");

    for(const LevelSector* sector: level.sectors){

        //BG
        this->lookForAsset(sector->backgroundName,
            SCENERY_DIR,
            ASSET_SCENERY,
            node,
            "\x1B[92m");

        //Tileset FG
        this->lookForAsset(sector->tilesetName,
            TILES_DIR,
            ASSET_TILESET,
            node,
            "\x1B[92m");

        //Tileset BG
        this->lookForAsset(sector->bgTilesetName,
            TILES_DIR,
            ASSET_TILESET,
            node,
            "\x1B[92m");

        //GFX texture
        this->lookForAsset(sector->gfxTextureName,
            GFX_DIR,
            ASSET_GFX,
            node,
            "\x1B[92m");
    }

    //Sprites
    for(const std::string& spriteName: level.spritesList){
        this->loadSpriteRecursive(spriteName, node);
    }
}

SpriteNode* Episode::loadSpriteRecursive(const std::string& name,Node *parent){
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
        for(Node * node: this->nodes){
            if(node->filename==name1 && node->type == ASSET_SPRITE){
                return dynamic_cast<SpriteNode*>(node);
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
            this->nodes.emplace_back(
                new MissingAsset(name, ASSET_SPRITE, parent)
            );

            return nullptr;
        }

        SpriteNode* spriteNode = new SpriteNode(name1, LoadSprite(*file));
        this->nodes.emplace_back(spriteNode);

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

        this->nodes.emplace_back(
            new MalformedAsset(name, ASSET_SPRITE, parent, e.what())
        );
    }

    return nullptr;
}

Node* Episode::lookForAsset(std::string name, const std::string& dir, int assetType, Node * parent,
        const std::string& color){
    //

    if(name.empty())return nullptr;
    
    name = PString::rtrim(PString::lowercase(name));
    for(Node * node:this->nodes){
        if(node->type == assetType && node->filename == name){
            return node;
        }
    }

    if(this->debug){
        std::cout<< "Looking for: "<<color<<"\""<<name<<"\"\x1B[0m"<<std::endl;
    }

    Node* result = nullptr;

    std::optional<File> file = this->findAsset(name, dir, "");
    if(!file.has_value()){
        if(this->debug){
            std::cout<<"\x1B[31mFile: \""<<name<<"\" not found!\x1B[0m"<<std::endl;
        }
        result = new MissingAsset(name, assetType, parent);
    }
    else{
        result = new Node(name, assetType, parent);
    }

    this->nodes.emplace_back(result);
    return result;
}

}