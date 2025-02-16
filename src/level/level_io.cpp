#include "level_io.hpp"
#include "utils/json_utils.hpp"
#include "level.hpp"
#include <fstream>
#include <sstream>

namespace libgreta{


void ReadLegacyStrInt(std::istream& in, int&val){
	char buffer[8];
    in.read(buffer, sizeof(buffer));
	buffer[7] = '\0';

	val = atoi(buffer);
}

static void ReadLegacyStrU32(std::istream& in, u32& val){
	char buffer[8];
    in.read(buffer, sizeof(buffer));
	buffer[7] = '\0';
	val = (u32)atol(buffer);
}


void ReadLegacyStr13Chars(std::istream& in, std::string & val){
	char buffer[13];
	in.read(buffer, sizeof(buffer));
	buffer[12] = '\0';
	val = buffer;
}

void ReadLegacyStr40Chars(std::istream& in, std::string & val){
	char buffer[40];
	in.read(buffer, sizeof(buffer));
	buffer[39] = '\0';
	val = buffer;
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

    Level level;

    std::string tileset_name, background_name, music_name;
	int weather = 0;
	int scrolling = 0;

	ReadLegacyStr13Chars(in, tileset_name);	
	ReadLegacyStr13Chars(in, background_name);
	ReadLegacyStr13Chars(in, music_name);


	char name_buffer[40];
	in.read(name_buffer, sizeof(name_buffer));
	name_buffer[39] = '\0';

	/**
	 * @brief 
	 * ???
	 * What's the purpose of this??
	 */
	for (int i = 38; i > 0 && (name_buffer[i] == (char)0xCD); i--)
		name_buffer[i] = 0;

	level.name = name_buffer;

	ReadLegacyStr40Chars(in, level.author);

	ReadLegacyStrInt(in, level.level_number);
	ReadLegacyStrInt(in, weather);

    /**
     * @brief 
     * useless unused data
     */
    u32 button_time = 0; 
	ReadLegacyStrU32(in, button_time);
    ReadLegacyStrU32(in, button_time);
    ReadLegacyStrU32(in, button_time);

    ReadLegacyStrInt(in, level.time);

	ReadLegacyStrInt(in, level.extra);

	ReadLegacyStrInt(in, scrolling);
	ReadLegacyStrInt(in, level.player_sprite_index);

	ReadLegacyStrInt(in, level.icon_x);
	ReadLegacyStrInt(in, level.icon_y);
	ReadLegacyStrInt(in, level.icon_id);

    // if(headerOnly){
	// 	file.close();
	// 	return;
	// }

	LevelSector* sector = new LevelSector(PK2_LEVEL_LEGACY_WIDTH, PK2_LEVEL_LEGACY_HEIGHT);
	level.sectors.push_back(sector);

	sector->backgroundName = background_name;
	sector->tilesetName = tileset_name;
	sector->musicName = music_name;

	sector->background_scrolling = scrolling;
	sector->weather = weather;

	// sprite prototypes

	u32 prototypesNumber = 0;
	ReadLegacyStrU32(in, prototypesNumber);
	if(prototypesNumber>PK2_LEVEL_LEGACY_MAX_PROTOTYPES){
		std::ostringstream os;
		os<<"Too many level sprite prototypes: "<<prototypesNumber<<std::endl;
		os<<PK2_LEVEL_LEGACY_MAX_PROTOTYPES<<" is the limit in the \"1.3\" level format";
		throw std::runtime_error(os.str());
	}

	char prototype_names_legacy[PK2_LEVEL_LEGACY_MAX_PROTOTYPES][13] = {""};
	
	in.read((char*)prototype_names_legacy, sizeof(prototype_names_legacy[0]) * prototypesNumber);

	level.spritesList.resize(prototypesNumber);

	for(u32 i=0;i<prototypesNumber;++i){
		char * prototype_name = prototype_names_legacy[i];
		prototype_name[12] = '\0';
		level.spritesList[i] = prototype_name;
	}

	// Background tiles
    ReadTilesArray(in, sector->background_tiles,
        PK2_LEVEL_LEGACY_WIDTH, PK2_LEVEL_LEGACY_HEIGHT, TILES_OFFSET_LEGACY);

    // Foreground tiles
    ReadTilesArray(in, sector->foreground_tiles,
        PK2_LEVEL_LEGACY_WIDTH, PK2_LEVEL_LEGACY_HEIGHT, TILES_OFFSET_LEGACY);

    // Sprite tiles
    ReadTilesArray(in, sector->sprite_tiles,
        PK2_LEVEL_LEGACY_WIDTH, PK2_LEVEL_LEGACY_HEIGHT, TILES_OFFSET_LEGACY);

    return level;
}

static Level LoadLevel15(std::istream& in){

    Level level;
    
    u32 sectors_number = 1;
    u32 compression = TILES_COMPRESSION_NONE;

    {
		const nlohmann::json j = ReadCBOR(in);
		jsonReadString(j, "name", level.name);
		jsonReadString(j, "author", level.author);
		jsonReadInt(j, "number",  level.level_number);
		jsonReadInt(j, "icon_x", level.icon_x);
		jsonReadInt(j, "icon_y", level.icon_y);
		jsonReadInt(j, "icon_id", level.icon_id);

		jsonReadU32(j, "sectors", sectors_number);
        jsonReadU32(j, "compression", compression);

		if(j.contains("sprite_prototypes")){
			level.spritesList = j["sprite_prototypes"].get<std::vector<std::string>>();
		}

		jsonReadInt(j, "player_index", level.player_sprite_index);
		jsonReadInt(j, "time", level.time);
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

		// Read sector header
		const nlohmann::json j = ReadCBOR(in);
		jsonReadU32(j, "width", width);
		jsonReadU32(j, "height", height);
		


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

        jsonReadInt(j, "rain_color", sector->rain_color);
        jsonReadString(j, "gfx", sector->gfxTextureName);


		// Background tiles
        ReadTilesArray(in, sector->background_tiles, width, height, compression);

		// Foreground tiles
		ReadTilesArray(in, sector->foreground_tiles, width, height, compression);

		// Sprite tiles
		ReadTilesArray(in, sector->sprite_tiles, width, height, compression);
	}

    return level;
}

static Level LoadLevel_stream(std::istream& f){
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

Level LoadLevel_s(const std::string& filename){
    std::ifstream f(filename, std::ios::binary);
    if(!f.good()){
        panicWhenFileNotFound(filename);
    }
    return LoadLevel_stream(f);
}

Level LoadLevel(const File& file){
    std::vector<char> buffer = file.getContent();
    if(buffer.size() < 5){
        throw std::runtime_error("Shit happened!");
    }

    std::string_view view(buffer.data(), buffer.size());
    std::istringstream f(std::string(view), std::ios::binary);
    return LoadLevel_stream(f);
}

void SaveLevel_s(const Level& level, const std::string& filename){
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
        j["number"] = level.level_number;
        j["icon_id"] = level.icon_id;
        j["icon_x"] = level.icon_x;
        j["icon_y"] = level.icon_y;

        j["sprite_prototypes"] = level.spritesList;
        j["player_index"] = level.player_sprite_index;

        j["sectors"] = u32(level.sectors.size());
        j["time"] = level.time;
        j["lua_script"] = level.lua_script;
        j["game_mode"] = level.game_mode;
        j["compression"] = 0;

        WriteCBOR(f, j);
    }

    for(const LevelSector* sector: level.sectors){
		nlohmann::json j;

		j["width"] = sector->getWidth();
		j["height"]= sector->getHeight();

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
        j["rain_color"] = sector->rain_color;

        j["gfx"] = sector->gfxTextureName;

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