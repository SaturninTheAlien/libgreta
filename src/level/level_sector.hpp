#pragma once

#include <string>

#include "tiles_array.hpp"
#include "utils/types.hpp"
#include "utils/api.hpp"

namespace libgreta{

class Level;

class GRETA_API LevelSector{
public:
    LevelSector(std::size_t width, std::size_t height):
        background_tiles(width*height),
        foreground_tiles(width*height),
        sprite_tiles(width*height),
        mWidth(width),
        mHeight(height)
        {

        }

    ~LevelSector()=default;
    std::size_t getWidth()const{
        return this->mWidth;
    }

    std::size_t getHeight()const{
        return this->mHeight;
    }

    std::size_t size()const{
        return this->background_tiles.size();
    }

    bool isCorrectTilePos(int pos_x, int pos_y)const{
        return pos_x>=0 && pos_y>=0 &&
        pos_x<(int)this->getWidth() && pos_y<(int)this->getHeight();
    }

    u8 getBGTile(int posX, int posY)const;
    u8 getFGTile(int posX, int posY)const;
    u8 getSpriteTile(int posX, int posY)const;

    void setBGTile(int posX, int posY, u8 value);
    void setFGTile(int posX, int posY, u8 value);
    void setSpriteTile(int posX, int posY, u8 value);

    /**
     * @brief 
     * Should be called after removing a sprite from the spriteList
     */
    void removeSprites(u8 index);

    std::string name;
    std::string tilesetName;
    std::string bgTilesetName;
    std::string backgroundName;
    std::string musicName;

    int weather = 0;
    int splash_color = -1; //based on the tileset
    int fire_color_1 = 64;  //red
    int fire_color_2 = 128; //orange
    
    int background_scrolling = 0;

    TilesArray background_tiles;
    TilesArray foreground_tiles;
    TilesArray sprite_tiles;

protected:
    const std::size_t mWidth;
    const std::size_t mHeight;
};

}