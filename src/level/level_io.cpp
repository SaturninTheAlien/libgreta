#include "level_io.hpp"
#include "utils/json_utils.hpp"
#include "level.hpp"
#include <fstream>
#include <sstream>

namespace libgreta{


static void ReadLegacyStrU32(std::istream& in, u32& val){
	char buffer[8];
    in.read(buffer, sizeof(buffer));
	buffer[7] = '\0';
	val = (u32)atol(buffer);
}

void WriteTilesArray(std::ostream& out, const TilesArray& array, int compression){
    if(compression!=TILES_COMPRESSION_NONE){
        throw std::runtime_error("Tiles compression not implemented yet!");
    }
    else{
        out.write((char*)array.mTiles, array.size());
    }
}

void ReadTilesArray(std::istream& in, TilesArray& array, u32 level_width,
        u32 level_height,
        int compression){
            
    switch (compression)
    {
    case TILES_COMPRESSION_NONE:
        in.read((char*)array.mTiles, array.size());
        break;

    case TILES_OFFSET_LEGACY:{
            u32 width = 0, height = 0;
            u32 offset_x = 0, offset_y = 0;

            ReadLegacyStrU32(in, offset_x);
            ReadLegacyStrU32(in, offset_y);
            ReadLegacyStrU32(in, width);
            ReadLegacyStrU32(in, height);

            in.read((char*)& offset_x, sizeof(u32));
            in.read((char*)& offset_y, sizeof(u32));
            in.read((char*)& width, sizeof(u32));
            in.read((char*)& height, sizeof(u32));

            for (u32 y = offset_y; y <= offset_y + height; y++) {
                u32 x_start = offset_x + y * level_width;
                /**
                 * @brief 
                 * To prevent a memory leak
                 */
                if(x_start>=0 && x_start + width < array.size()){
                    in.read((char*)&array.mTiles[x_start], width + 1);
                }
                else{
                    throw std::runtime_error("Malformed level file!");
                }
            }

        }
        break;
    
    case TILES_OFFSET_NEW:{
            u32 width = 0, height = 0;
            u32 offset_x = 0, offset_y = 0;

            in.read((char*)& offset_x, sizeof(u32));
            in.read((char*)& offset_y, sizeof(u32));
            in.read((char*)& width, sizeof(u32));
            in.read((char*)& height, sizeof(u32));

            for (u32 y = offset_y; y <= offset_y + height; y++) {
                u32 x_start = offset_x + y * level_width;
                /**
                 * @brief 
                 * To prevent a memory leak
                 */
                if(x_start>=0 && x_start + width < array.size()){
                    in.read((char*)&array.mTiles[x_start], width + 1);
                }
                else{
                    throw std::runtime_error("Malformed level file!");
                }
            }

        }
        break;
    
    default:
        break;
    }
}


static Level LoadLevel13(std::istream& in){
    throw std::runtime_error("Not implemented yet!");
}

static Level LoadLevel15(std::istream& in){

    Level level;
    
    u32 sectors_number = 1;

    {
		const nlohmann::json j = ReadCBOR(in);
		jsonReadString(j, "name", level.name);
		jsonReadString(j, "author", level.author);
		jsonReadInt(j, "level_number",  level.level_number);
		jsonReadInt(j, "icon_x", level.icon_x);
		jsonReadInt(j, "icon_y", level.icon_y);
		jsonReadInt(j, "icon_id", level.icon_id);

		jsonReadU32(j, "regions", sectors_number);

		if(j.contains("sprite_prototypes")){
			level.spritesList = j["sprite_prototypes"].get<std::vector<std::string>>();
		}

		jsonReadInt(j, "player_index", level.player_sprite_index);
		jsonReadInt(j, "map_time", level.map_time);
		jsonReadString(j, "lua_script", level.lua_script);
		jsonReadInt(j, "game_mode", level.game_mode);
	}

    if(sectors_number==0){
		throw std::runtime_error("Bad level! At least one level sector is required!");
	}

    level.sectors.resize(sectors_number);
	for(u32 i=0;i<sectors_number;++i){
		u32 width = 0; // placeholder
		u32 height = 0; //placeholder
		u32 compression = 0;

		// Read sector header
		const nlohmann::json j = ReadCBOR(in);
		jsonReadU32(j, "width", width);
		jsonReadU32(j, "height", height);
		jsonReadU32(j, "compression", compression);


        LevelSector*sector = new LevelSector(width, height);
        level.sectors[i] = sector;

        sector->tilesetName = j["tileset"].get<std::string>();

        if(j.contains("tileset_bg") && j["tileset_bg"].is_string()){
            sector->bgTilesetName = j["tileset_bg"].get<std::string>();
        }
        else{
            sector->bgTilesetName = "";
        }

        sector->backgroundName = j["background"].get<std::string>();

		jsonReadString(j, "music", sector->musicName);
		jsonReadInt(j, "scrolling", sector->background_scrolling);
		jsonReadInt(j, "weather", sector->weather);

		jsonReadInt(j, "splash_color", sector->splash_color);
		jsonReadInt(j, "fire_color_1", sector->fire_color_1);
		jsonReadInt(j, "fire_color_2", sector->fire_color_2);


		// Background tiles
        ReadTilesArray(in, sector->background_tiles, width, height, compression);

		// Foreground tiles
		ReadTilesArray(in, sector->foreground_tiles, width, height, compression);

		// Sprite tiles
		ReadTilesArray(in, sector->sprite_tiles, width, height, compression);
	}

    return level;
}

Level LoadLevel(const std::string& filename){
    std::ifstream f(filename, std::ios::binary);
    if(!f.good()){
         throw std::runtime_error("Cannot read a file: "+filename);
    }
    
    char version[5];
    f.read(version, sizeof(version));    
    version[4] = '\0';

    if(strcmp(version, "1.5")==0){
        return LoadLevel15(f);
    }
    else if(strcmp(version, "1.3")==0){
        return LoadLevel13(f);
    }
    else{
        std::ostringstream os;
        os<<"Unknown level format: "<<version<<std::endl;
        throw std::runtime_error(os.str());
    }
}
void SaveLevel(const Level& level, const std::string& filename){
    std::ofstream f(filename, std::ios::binary);
    if(!f.good()){
         throw std::runtime_error("Unable to save level!");
    }

    char version[5] = "1.5";
	f.write(version, sizeof(version));


    //Write header
    {
        nlohmann::json j;
        j["name"] = level.name;
        j["author"] = level.author;
        j["level_number"] = level.level_number;
        j["icon_id"] = level.icon_id;
        j["icon_x"] = level.icon_x;
        j["icon_y"] = level.icon_y;

        j["sprite_prototypes"] = level.spritesList;
        j["player_index"] = level.player_sprite_index;

        j["regions"] = u32(level.sectors.size());
        j["map_time"] = level.map_time;
        j["lua_script"] = level.lua_script;
        j["game_mode"] = level.game_mode;

        WriteCBOR(f, j);
    }

    for(const LevelSector* sector: level.sectors){
		nlohmann::json j;

		j["width"] = sector->getWidth();
		j["height"]= sector->getHeight();
		j["compression"] = 0;

		j["tileset"] = sector->tilesetName;
		if(sector->bgTilesetName!=""){
			j["tileset_bg"] = sector->bgTilesetName;
		}

		
		j["music"] = sector->musicName;
		j["background"] = sector->backgroundName;
		j["scrolling"] = sector->background_scrolling;
		j["weather"] = sector->weather;

		j["splash_color"] = sector->splash_color;
		j["fire_color_1"] = sector->fire_color_1;
		j["fire_color_2"] = sector->fire_color_2;

		WriteCBOR(f, j);

		//background tiles
        WriteTilesArray(f, sector->background_tiles, 0);

		//foreground tiles
        WriteTilesArray(f, sector->foreground_tiles, 0);

		//sprite tiles
        WriteTilesArray(f, sector->sprite_tiles, 0);
	}


    f.close();
}

}