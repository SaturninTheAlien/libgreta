#include "level.hpp"
#include <iostream>

namespace libgreta{

Level::Level(){
}

Level::~Level(){
    for(LevelSector*& sector: this->sectors){
        if(sector!=nullptr){
            delete sector;
            sector = nullptr;
        }
    }
    this->sectors.clear();
}

Level::Level(const Level& src):
    name(src.name),
    author(src.author),
    spritesList(src.spritesList),

    level_number(src.level_number),
    time(src.time),
    extra(src.extra),
    player_sprite_index(src.player_sprite_index),
    icon_x(src.icon_x),
    icon_y(src.icon_y),
    icon_id(src.icon_id)

{

    std::size_t sectors_number = src.sectors.size();
    this->sectors.resize(sectors_number);
    for(std::size_t i=0;i<sectors_number;++i){
        
        this->sectors[i] = new LevelSector(*src.sectors[i]);
    }
}

Level::Level(Level&& src):
    name(std::move(src.name)),
    author(std::move(src.author)),
    sectors(std::move(src.sectors)),
    spritesList(std::move(src.spritesList)),

    level_number(src.level_number),
    time(src.time),
    extra(src.extra),
    player_sprite_index(src.player_sprite_index),
    icon_x(src.icon_x),
    icon_y(src.icon_y),
    icon_id(src.icon_id)
{
}

}