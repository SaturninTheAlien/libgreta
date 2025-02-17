#include "crawler.hpp"
#include "files/pk2filesystem.hpp"
#include "utils/string_utils.hpp"
#include "sprite/sprite_io.hpp"
#include <iostream>


namespace libgreta{

PK2Crawler::~PK2Crawler(){
    for(SpriteNode*& proto:this->spriteNodes){
        if(proto!=nullptr){
            delete proto;
            proto = nullptr;
        }
    }

    this->spriteNodes.clear();
}


SpriteNode* PK2Crawler::loadSpriteRecursive(const std::string& name,int requiredFrom,void*parent){
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
        for(SpriteNode* spriteNode: this->spriteNodes){
            if(spriteNode->filename==name1){
                return spriteNode;
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
            this->missingAssets.emplace_back(MissingAsset(name, MISSING_SPRITE, requiredFrom, parent));
            return nullptr;
        }

        SpriteNode* spriteNode = new SpriteNode(name1, LoadSprite(*file));
        this->spriteNodes.emplace_back(spriteNode);

        const SpritePrototype& proto = spriteNode->prototype;

        //texture
        this->lookForTexture(spriteNode);
        
        //sounds
        for(const std::string& soundName: proto.sounds){
            this->lookForSound(spriteNode, soundName);
        }

        //bonus
        spriteNode->bonus = this->loadSpriteRecursive(proto.bonus_str, REQUIRED_BONUS, spriteNode);

        //ammo1
        spriteNode->ammo1 = this->loadSpriteRecursive(proto.ammo1_str, REQUIRED_AMMO1, spriteNode);

        //ammo2
        spriteNode->ammo2 = this->loadSpriteRecursive(proto.ammo2_str, REQUIRED_AMMO2, spriteNode);

        //transformation
        spriteNode->transformation = this->loadSpriteRecursive(proto.transformation_str,
            REQUIRED_TRANSFORMATION, spriteNode);

        


        return spriteNode;

    }
    catch(const std::exception& e){
        this->missingAssets.emplace_back(MissingAsset(name, MISSING_SPRITE, requiredFrom, parent, e.what()));
    }

    return nullptr;
}

void PK2Crawler::lookForTexture(SpriteNode* node){

    std::string textureName = PString::rtrim(PString::lowercase(
        node->prototype.picture_filename
    ));

    for(const std::string& str:this->spriteTextures){
        if(str==textureName)return;
    }

    this->spriteTextures.emplace_back(textureName);

    if(this->verbose){
        std::cout<<"\x1B[36mLooking for: \""<<textureName<<"\"\x1B[0m"<<std::endl;
    }

    std::optional<File> file = FindAsset(textureName, SPRITES_DIR);
    if(!file.has_value()){
        if(this->verbose){
            std::cout<<"\x1B[31mTexture: \""<<textureName<<"\" not found!\x1B[0m"<<std::endl;
        }

        this->missingAssets.emplace_back(MissingAsset(textureName,
                        MISSING_SPRITE_TEXTURE,
                        0,
                        node));
    }
}

void PK2Crawler::lookForSound(SpriteNode*node, const std::string& soundName){

    //Intentionally no sound
    if(soundName.empty())return;

    for(const std::string& str:this->spriteSounds){
        if(soundName==str)return;
    }
    this->spriteSounds.emplace_back(soundName);

    if(this->verbose){
        std::cout<<"\x1B[34mLooking for: \""<<soundName<<"\"\x1B[0m"<<std::endl;
    }

    std::optional<File> file = FindAsset(soundName, SPRITES_DIR);
    if(!file.has_value()){
        if(this->verbose){
            std::cout<<"\x1B[31mSFX: \""<<soundName<<"\" not found!\x1B[0m"<<std::endl;
        }

        this->missingAssets.emplace_back(MissingAsset(soundName,
                        MISSING_SPRITE_SOUND,
                        0,
                        node));
    }
}

}