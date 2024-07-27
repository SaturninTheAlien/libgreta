#include "level_sector.hpp"
#include <stdexcept>
#include <cstring>

namespace libgreta{

u8 LevelSector::getBGTile(int posX, int posY)const{
    if(this->isCorrectTilePos(posX, posY)){
        return this->background_tiles[this->getWidth()*posY + posX];
    }
    return 255;
}

u8 LevelSector::getFGTile(int posX, int posY)const{
    if(this->isCorrectTilePos(posX, posY)){
        return this->foreground_tiles[this->getWidth()*posY + posX];
    }
    return 255;
}

u8 LevelSector::getSpriteTile(int posX, int posY)const{
    if(this->isCorrectTilePos(posX, posY)){
        return this->sprite_tiles[this->getWidth()*posY + posX];
    }
    return 255;
}

void LevelSector::setFGTile(int posX, int posY, u8 value){
    if(this->isCorrectTilePos(posX, posY)){
        this->foreground_tiles[this->getWidth()*posY + posX] = value;
    }
}

void LevelSector::setBGTile(int posX, int posY, u8 value){
    if(this->isCorrectTilePos(posX, posY)){
        this->background_tiles[this->getWidth()*posY + posX] = value;
    }
}

void LevelSector::setSpriteTile(int posX, int posY, u8 value){
    if(this->isCorrectTilePos(posX, posY)){
        this->sprite_tiles[this->getWidth()*posY + posX] = value;
    }
}

void LevelSector::removeSprites(u8 index){
    for(std::size_t i=0;i<this->size();++i){
        u8& spriteTile = this->sprite_tiles[i];
        if(spriteTile!=255){

            if(spriteTile==index){
                spriteTile=255;
            }
            else if(spriteTile > index){
                spriteTile -= 1;
            }
        }
    }
}



}