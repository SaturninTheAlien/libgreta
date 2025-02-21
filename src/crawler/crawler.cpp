#include "crawler.hpp"
#include "files/pk2filesystem.hpp"
#include "utils/string_utils.hpp"
#include "sprite/sprite_io.hpp"
#include <iostream>


namespace libgreta{

PK2Crawler::~PK2Crawler(){
    for(Node*& proto:this->nodes){
        if(proto!=nullptr){
            delete proto;
            proto = nullptr;
        }
    }

    this->nodes.clear();
}


SpriteNode* PK2Crawler::loadSpriteRecursive(const std::string& name,Node *parent){
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

        if(this->verbose){
            std::cout<<"\x1B[32mLooking for: \""<<name1<<"\"\x1B[0m"<<std::endl;
        }

        std::optional<File> file = FindAsset(name1, SPRITES_DIR, ".spr");
        if(!file.has_value()){

            if(this->verbose){
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
                spriteNode);
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

Node* PK2Crawler::lookForAsset(std::string name, const std::string& dir, int assetType, Node * parent,
        const std::string& color){
    //

    if(name.empty())return nullptr;
    
    name = PString::rtrim(PString::lowercase(name));
    for(Node * node:this->nodes){
        if(node->type == assetType && node->filename == name){
            return node;
        }
    }

    if(this->verbose){
        std::cout<< color << "Looking for: \""<<name<<"\"\x1B[0m"<<std::endl;
    }

    Node* result = nullptr;

    std::optional<File> file = FindAsset(name, dir);
    if(!file.has_value()){
        if(this->verbose){
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