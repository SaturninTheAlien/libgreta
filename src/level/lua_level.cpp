
#include "3rd_party/sol.hpp"
#include "level.hpp"
#include "level_sector.hpp"

namespace libgreta{

void ExposeLevelClasses(sol::table& t){

    t.new_usertype<LevelSector>("LevelSector",

    "name", &LevelSector::name,
    "tileset", &LevelSector::tilesetName,
    "bgTileset", &LevelSector::bgTilesetName,
    "background", &LevelSector::backgroundName,
    "music", &LevelSector::musicName,

    "weather", &LevelSector::weather,
    "splash_color", &LevelSector::splash_color,
    "fire_color_1", &LevelSector::fire_color_1,
    "fire_color_2", &LevelSector::fire_color_2,

    "getWidth", &LevelSector::getWidth,
    "getHeight", &LevelSector::getHeight,
    "size", &LevelSector::size,
    "isCorrectTilePos", &LevelSector::isCorrectTilePos,
    
    "getBGTile", &LevelSector::getBGTile,
    "getFGTile", &LevelSector::getFGTile,
    "getSpriteTile", &LevelSector::getSpriteTile,
    
    "setBGTile", &LevelSector::setBGTile,
    "setFGTile", &LevelSector::setFGTile,
    "setSpriteTile", &LevelSector::setSpriteTile);

    t.new_usertype<Level>("Level",
    "name", &Level::name,
    "author", &Level::author,

    //"sectors", &Level::sectors,
    "spritesList", &Level::spritesList,


    "level_number", &Level::level_number,
    "map_time", &Level::map_time,
    "extra", &Level::extra,
    "player_sprite_index", &Level::player_sprite_index,

    "icon_x", &Level::icon_x,
    "icon_y", &Level::icon_y,
    "icon_id", &Level::icon_id,

    "lua_script", &Level::lua_script);

}

}
