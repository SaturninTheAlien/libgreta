
#include "3rd_party/sol.hpp"
#include "../../level/level.hpp"
#include "../../level/level_sector.hpp"
#include "../../level/level_io.hpp"

namespace libgreta{

static LevelSector* NewLevelSector(Level* level, std::size_t width, std::size_t height){
    if(level==nullptr) return nullptr;

    LevelSector*sector = new LevelSector(width, height);
    level->sectors.push_back(sector);

    return sector;
}

static LevelSector* CloneLevelSector(Level* level, int id){
    id-=1; //for the lua convention

    if(level==nullptr || id<0 || id>= (int)level->sectors.size())return nullptr;

    LevelSector*sector = new LevelSector(*level->sectors[id]);
    level->sectors.push_back(sector);

    return sector;
}

static void DeleteLevelSector(Level*level, int id){
    id-=1; //for the lua convention
    if(level==nullptr || id<0 || id>= (int)level->sectors.size())return;

    delete level->sectors[id];
    level->sectors[id] = nullptr;
    level->sectors.erase(level->sectors.begin() + id);    
}


void ExposeLevelClasses(sol::table& t){

    t.new_usertype<LevelSector>("LevelSector",
    sol::no_constructor,
    "name", &LevelSector::name,
    "tileset", &LevelSector::tilesetName,
    "bgTileset", &LevelSector::bgTilesetName,
    "background", &LevelSector::backgroundName,
    "music", &LevelSector::musicName,

    "weather", &LevelSector::weather,
    "splash_color", &LevelSector::splash_color,
    "fire_color_1", &LevelSector::fire_color_1,
    "fire_color_2", &LevelSector::fire_color_2,
    "rain_color", &LevelSector::rain_color,
    "gfxTexture", &LevelSector::gfxTextureName,

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

    "sectors", sol::readonly(&Level::sectors),
    "spritesList", &Level::spritesList,


    "level_number", &Level::level_number,
    "time", &Level::time,
    "extra", &Level::extra,
    "player_sprite_index", &Level::player_sprite_index,

    "icon_x", &Level::icon_x,
    "icon_y", &Level::icon_y,
    "icon_id", &Level::icon_id,

    "lua_script", &Level::lua_script,
    
    "newSector", NewLevelSector,
    "cloneSector", CloneLevelSector,
    "deleteSector", DeleteLevelSector);
}

void ExposeLevelIO(sol::table& t){
    t["loadLevel"] = sol::overload(LoadLevel_s, LoadLevel);
    t["saveLevel"] = SaveLevel_s;
}

}
