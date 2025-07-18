#include <pybind11/stl.h>
#include "py_level.hpp"

#include "level/level.hpp"
#include "level/level_io.hpp"

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


void ExposeLevel(pybind11::module_ & m){
    pybind11::class_<LevelSector>(m, "LevelSector")
        .def(pybind11::init<std::size_t, std::size_t>())
        .def_readwrite("name", &LevelSector::name)
        .def_readwrite("tileset", &LevelSector::tilesetName)
        .def_readwrite("bgTileset", &LevelSector::bgTilesetName)
        .def_readwrite("background", &LevelSector::backgroundName)
        .def_readwrite("music", &LevelSector::musicName)
        .def_readwrite("weather", &LevelSector::weather)
        .def_readwrite("splash_color", &LevelSector::splash_color)
        .def_readwrite("fire_color_1", &LevelSector::fire_color_1)
        .def_readwrite("fire_color_2", &LevelSector::fire_color_2)
        .def_readwrite("rain_color", &LevelSector::rain_color)
        .def_readwrite("gfxTexture", &LevelSector::gfxTextureName)
        .def("getWidth", &LevelSector::getWidth)
        .def("getHeight", &LevelSector::getHeight)
        .def("size", &LevelSector::size)
        .def("isCorrectTilePos", &LevelSector::isCorrectTilePos)
        .def("getBGTile", &LevelSector::getBGTile)
        .def("getFGTile", &LevelSector::getFGTile)
        .def("getSpriteTile", &LevelSector::getSpriteTile)
        .def("setBGTile", &LevelSector::setBGTile)
        .def("setFGTile", &LevelSector::setFGTile)
        .def("setSpriteTile", &LevelSector::setSpriteTile);

    pybind11::class_<Level>(m, "Level")
        .def(pybind11::init<>())
        .def_readwrite("name", &Level::name)
        .def_readwrite("author", &Level::author)
        .def_readonly("sectors", &Level::sectors)
        .def_readwrite("sprite_list", &Level::spritesList)
        .def_readwrite("level_number", &Level::level_number)
        .def_readwrite("time", &Level::time)
        .def_readwrite("extra", &Level::extra)
        .def_readwrite("player_sprite_index", &Level::player_sprite_index)
        .def_readwrite("icon_x", &Level::icon_x)
        .def_readwrite("icon_y", &Level::icon_y)
        .def_readwrite("icon_id", &Level::icon_id)
        .def_readwrite("lua_script", &Level::lua_script)
        .def("new_sector", NewLevelSector)
        .def("clone_sector", CloneLevelSector)
        .def("delete_sector", DeleteLevelSector);

}
void ExposeLevelIO(pybind11::module_ & m){
    m.def("load_level", LoadLevel);
    m.def("load_level_s", LoadLevel_s);    
}

}