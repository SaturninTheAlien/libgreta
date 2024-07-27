#pragma once
#include <vector>
#include "level_sector.hpp"
#include <string>

namespace libgreta{

class GRETA_API Level{
public:
    Level();
    ~Level();
    Level(const Level& src);
    Level(Level&& src);

    Level& operator=(const Level& src) = delete;

    std::string name;
    std::string author;   

    std::vector<LevelSector*> sectors;
    std::vector<std::string> spritesList;

    int      level_number          = 0;                            // level of the episode
    int      map_time           = 0;                            // map time (in (dec)conds)
    int      extra          = 0;                            // extra config - not used

    int      player_sprite_index = 0;                            // player prototype

    int      icon_x = 0;                                         // map icon x pos
	int      icon_y = 0;                                         // map icon x pos
    int      icon_id = 0;                                        // icon id

    std::string lua_script = "main.lua";                        // lua script
    int game_mode = 0;                                          // game mode  
};

}