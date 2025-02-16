#include "sprite.hpp"
#include "sprite_legacy.hpp"
#include "utils/json_utils.hpp"

namespace libgreta{

SpriteAnimation::SpriteAnimation(const LegacySprAnimation& anim){
	this->loop = anim.loop;
	this->sequence = std::vector<int>(anim.sequence, anim.sequence + anim.frames);
}


void to_json(nlohmann::json& j, const SpriteAnimation& a){
	j["loop"] = a.loop;
	j["sequence"] = a.sequence;

	if(a.intro > 0){
		j["intro"] = a.intro;
	}
}

void from_json(const nlohmann::json&j, SpriteAnimation& a){
	a.loop = j["loop"].get<bool>();
	a.sequence = j["sequence"].get<std::vector<int>>();

	if(j.contains("intro")){
		a.intro = j["intro"].get<unsigned int>();
		if(a.intro >= a.sequence.size()){
			a.intro = 0;
		}
	}
}

/**
 * @brief 
 * To prevent segfault while reading malformed sprites in the legacy formats.
 */
inline static std::string ReadLegacyString(char*arr, std::size_t n){
	arr[n-1] = '\0';
	return std::string(arr);
}

SpritePrototype::SpritePrototype(PrototypeClass10 &proto){
	this->picture_filename = ReadLegacyString(proto.picture, 13);
	this->name = ReadLegacyString(proto.name, 30);

	this->transformation_str = ReadLegacyString(proto.transformation_str, 13);
	this->bonus_str = ReadLegacyString(proto.bonus_str, 13);
	this->ammo1_str = ReadLegacyString(proto.ammo1_str, 13);
	this->ammo2_str = ReadLegacyString(proto.ammo2_str, 13);

	for (int i=0;i<SPRITE_SOUNDS_NUMBER_LEGACY;i++) {
		this->sound_files[i] = ReadLegacyString(proto.sound_files[i], 13);
		this->sounds[i] = proto.sounds[i];
	}

	//animations_number		= proto.animations_number;
	can_open_locks				= proto.can_open_locks;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	score				= proto.score;
	immunity_type				= proto.immunity_type;
	
	destruction_effect		= proto.how_destroyed;
	if(destruction_effect==FX_DESTRUCT_NO_EFFECT){
		indestructible = true;
	}

	type				= proto.sprite_type;
	damage				= proto.damage;
	color				= proto.color;
	enemy			= proto.enemy;


	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}
SpritePrototype::SpritePrototype(PrototypeClass11 &proto){
	this->picture_filename = ReadLegacyString(proto.picture, 13);
	this->name = ReadLegacyString(proto.name, 30);

	this->transformation_str = ReadLegacyString(proto.transformation_str, 13);
	this->bonus_str = ReadLegacyString(proto.bonus_str, 13);
	this->ammo1_str = ReadLegacyString(proto.ammo1_str, 13);
	this->ammo2_str = ReadLegacyString(proto.ammo2_str, 13);

	for (int i=0;i<SPRITE_SOUNDS_NUMBER_LEGACY;i++) {
		this->sound_files[i] = ReadLegacyString(proto.sound_files[i], 13);
		this->sounds[i] = proto.sounds[i];
	}

	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	
	destruction_effect		= proto.how_destroyed;
	if(destruction_effect==FX_DESTRUCT_NO_EFFECT){
		indestructible = true;
	}

	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}
SpritePrototype::SpritePrototype(PrototypeClass12 &proto){

	this->picture_filename = ReadLegacyString(proto.picture, 13);
	this->name = ReadLegacyString(proto.name, 30);

	this->transformation_str = ReadLegacyString(proto.transformation_str, 13);
	this->bonus_str = ReadLegacyString(proto.bonus_str, 13);
	this->ammo1_str = ReadLegacyString(proto.ammo1_str, 13);
	this->ammo2_str = ReadLegacyString(proto.ammo2_str, 13);

	for (int i=0;i<SPRITE_SOUNDS_NUMBER_LEGACY;i++) {
		this->sound_files[i] = ReadLegacyString(proto.sound_files[i], 13);
		this->sounds[i] = proto.sounds[i];
	}

	sound_frequency			= proto.sound_frequency;
	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	is_wall_up			= proto.is_wall_up;
	is_wall_down			= proto.is_wall_down;
	is_wall_right		= proto.is_wall_right;
	is_wall_left		= proto.is_wall_left;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	random_sound_frequency			= proto.random_sound_frequency;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	check_tiles		= proto.check_tiles;
	
	destruction_effect		= proto.how_destroyed;
	if(destruction_effect==FX_DESTRUCT_NO_EFFECT){
		indestructible = true;
	}

	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}



SpritePrototype::SpritePrototype(PrototypeClass13 &proto){
	this->picture_filename = ReadLegacyString(proto.picture, 100); //proto.picture;
	this->name = ReadLegacyString(proto.name, 30); //proto.name;

	this->transformation_str = ReadLegacyString(proto.transformation_str, 100); //proto.transformation_str;
	this->bonus_str = ReadLegacyString(proto.bonus_str, 100);  //proto.bonus_str;
	this->ammo1_str = ReadLegacyString(proto.ammo1_str, 100); //proto.ammo1_str;
	this->ammo2_str = ReadLegacyString(proto.ammo2_str, 100);  //proto.ammo2_str;

	for (int i=0;i<SPRITE_SOUNDS_NUMBER_LEGACY;i++) {
		this->sound_files[i] = ReadLegacyString(proto.sound_files[i], 100);
		this->sounds[i] = proto.sounds[i];
	}

	sound_frequency			= proto.sound_frequency;
	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	is_wall_up			= proto.is_wall_up;
	is_wall_down			= proto.is_wall_down;
	is_wall_right		= proto.is_wall_right;
	is_wall_left		= proto.is_wall_left;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	random_sound_frequency			= proto.random_sound_frequency;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	check_tiles		= proto.check_tiles;
	
	destruction_effect		= proto.how_destroyed;
	if(destruction_effect==FX_DESTRUCT_NO_EFFECT){
		indestructible = true;
	}

	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	effect		= proto.effect;
	is_transparent				= proto.is_transparent;
	projectile_charge_time			= proto.projectile_charge_time;
	can_glide			= proto.can_glide;
	//boss				= proto.boss;
	bonus_always			= proto.bonus_always;
	can_swim			= proto.can_swim;

	for (int i=0;i<10;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}

const std::map<std::string,int> SpritePrototype::AnimationsDict = {
	{"idle", ANIMATION_IDLE},
    {"walking", ANIMATION_WALKING},
    {"jump_up", ANIMATION_JUMP_UP},
    {"jump_down", ANIMATION_JUMP_DOWN},
    {"squat", ANIMATION_SQUAT},
    {"damage", ANIMATION_DAMAGE},
    {"death", ANIMATION_DEATH},
    {"attack1", ANIMATION_ATTACK1},
    {"attack2", ANIMATION_ATTACK2}
};

const std::map<std::string,int> SpritePrototype::SoundTypesDict={
    {"damage", SOUND_DAMAGE},
    {"destruction", SOUND_DESTRUCTION},
    {"attack1", SOUND_ATTACK1},
    {"attack2", SOUND_ATTACK2},
    {"random", SOUND_RANDOM},
    {"special1", SOUND_SPECIAL1},
    {"special2", SOUND_SPECIAL2}
};

const std::map<std::string,u8> SpritePrototype::ColorsDict={
	{"gray", COLOR_GRAY},
	{"blue", COLOR_BLUE},
	{"red", COLOR_RED},
	{"green", COLOR_GREEN},
	{"orange", COLOR_ORANGE},
	{"violet", COLOR_VIOLET},
	{"turquoise", COLOR_TURQUOISE},
	{"normal", COLOR_NORMAL}
};

SpritePrototype::SpritePrototype(const nlohmann::json& j){
	if(j.contains("ai")){
		this->AI_v.clear();
		this->AI_v = j["ai"].get<std::vector<int>>();
	}

	jsonReadString(j, "ammo1", this->ammo1_str);


	jsonReadString(j, "ammo2", this->ammo2_str);

	if(j.contains("animations")){
		const nlohmann::json& j_animations = j["animations"]; 
		for(std::pair<std::string, int> p: AnimationsDict){
			if(j_animations.contains(p.first)){
				this->animations[p.second] = j_animations[p.first].get<SpriteAnimation>();
			}
		}
	}

	jsonReadBool(j, "always_active", this->always_active);

	jsonReadInt(j, "attack1_time", this->attack1_time);

	jsonReadInt(j, "attack2_time", this->attack2_time);

	jsonReadBool(j, "bonus_always", this->bonus_always);

	jsonReadString(j, "bonus", this->bonus_str);

	jsonReadInt(j, "bonuses_number", this->bonuses_number);

	jsonReadBool(j, "can_glide", this->can_glide);

	jsonReadBool(j, "can_open_locks", this->can_open_locks);

	jsonReadBool(j, "can_swim", this->can_swim);

	jsonReadInt(j, "charge_time", this->charge_time);

	jsonReadEnumU8(j, "color", this->color, ColorsDict);

	jsonReadInt(j, "damage", this->damage);

	jsonReadInt(j, "damage_type", this->damage_type);

	jsonReadEnumU8(j, "effect", this->effect);

	jsonReadBool(j, "enemy", this->enemy);

	jsonReadInt(j, "energy", this->energy);

	if(j.contains("frame")){
		const nlohmann::json& j_frame = j["frame"];
		this->picture_frame_x = j_frame["pos_x"].get<int>();
		this->picture_frame_y = j_frame["pos_y"].get<int>();
		this->picture_frame_width  = j_frame["width"].get<int>();
		this->picture_frame_height = j_frame["height"].get<int>();
	}

	jsonReadInt(j, "frame_rate", this->frame_rate);

	jsonReadInt(j, "frames_number", this->frames_number);

	/**
	 * @brief 
	 * Obsolete field
	 */
	if(j.contains("how_destroyed")){
		int how_destroyed = j["how_destroyed"].get<int>();

		this->destruction_effect = how_destroyed;
		if(this->destruction_effect == FX_DESTRUCT_NO_EFFECT){
			this->indestructible = true;
		}
	}

	jsonReadInt(j, "destruction_effect", this->destruction_effect);
	jsonReadBool(j, "indestructible", this->indestructible);

	jsonReadInt(j, "immunity_type", this->immunity_type);

	jsonReadBool(j, "is_transparent", this->is_transparent);

	jsonReadBool(j, "is_wall", this->is_wall);

	jsonReadBool(j, "is_wall_down", this->is_wall_down);

	jsonReadBool(j, "is_wall_left", this->is_wall_left);

	jsonReadBool(j, "is_wall_right", this->is_wall_right);

	jsonReadBool(j, "is_wall_up", this->is_wall_up);

	jsonReadBool(j, "check_tiles", this->check_tiles);

	jsonReadInt(j, "max_jump", this->max_jump);

	jsonReadDouble(j, "max_speed", this->max_speed);

	jsonReadString(j, "name", this->name);

	jsonReadInt(j, "parallax_type", this->parallax_type);

	jsonReadString(j, "picture", this->picture_filename);

	jsonReadInt(j, "projectile_charge_time", this->projectile_charge_time);

	jsonReadBool(j, "random_sound_frequency", this->random_sound_frequency);

	jsonReadInt(j, "score", this->score);

	if(j.contains("size")){
		const nlohmann::json& size = j["size"];
		this->width = size["width"].get<int>();
		this->height = size["height"].get<int>();
	}

	jsonReadInt(j, "sound_frequency", this->sound_frequency);

	if(j.contains("sounds")){
		const nlohmann::json& j_sounds = j["sounds"];
		for(std::pair<std::string, int> p: SoundTypesDict){
			this->sounds[p.second] = -1;
			jsonReadString(j_sounds, p.first, this->sound_files[p.second]);
		}
	}

	jsonReadString(j, "transformation", this->transformation_str);

	jsonReadInt(j, "type", this->type);

	jsonReadBool(j, "vibrates", this->vibrates);

	jsonReadDouble(j, "weight", this->weight);

	jsonReadInt(j, "info_id", this->info_id);

	if(j.contains("commands")){
		this->commands_json = j["commands"];
	}

	if(j.contains("dead_weight") && j["dead_weight"].is_number()){
		this->has_dead_weight = true;
		this->dead_weight = j["dead_weight"].get<double>();
	}

	if(j.contains("attack1_offset") && !j["attack1_offset"].is_null()){
		this->attack1_offset = j["attack1_offset"].get<Point2D>();
	}

	if(j.contains("attack2_offset") && !j["attack2_offset"].is_null()){
		this->attack2_offset = j["attack2_offset"].get<Point2D>();
	}
}

void to_json(nlohmann::json& j, const SpritePrototype& c){
	using json = nlohmann::json;

    j["version"] = "2.0";

    j["type"] = c.type;
    j["picture"] = c.picture_filename;

    json sounds;
    for(std::pair<std::string, int> p: SpritePrototype::SoundTypesDict){
        sounds[p.first] = c.sound_files[p.second];        
    }

    j["sounds"] = sounds;
    j["frames_number"] = c.frames_number;
    j["frame_rate"] = c.frame_rate;

    json animations;
    for(std::pair<std::string, int> p :SpritePrototype::AnimationsDict){
        animations[p.first] = c.animations[p.second];
    }

    j["animations"] = animations;


    json frame;
    frame["pos_x"] = c.picture_frame_x;
    frame["pos_y"] = c.picture_frame_y;
    frame["width"] = c.picture_frame_width;
    frame["height"] = c.picture_frame_height;

    j["frame"] = frame;

    j["name"] = c.name;
    json size;
	size["width"]  = c.width;
	size["height"] = c.height;

	j["size"] = size;
    j["weight"] = c.weight;
    j["enemy"] = c.enemy;
    j["energy"] = c.energy;
    j["damage"] = c.damage;
    j["damage_type"] = c.damage_type;
    j["immunity_type"] = c.immunity_type;
    j["score"] = c.score;

    j["ai"] = c.AI_v;
    j["max_jump"] = c.max_jump;
    j["max_speed"] = c.max_speed;
    j["charge_time"] = c.charge_time;

	j["color"] = c.color;

	for(std::pair<std::string, u8> p:SpritePrototype::ColorsDict){
		if(p.second==c.color){
			j["color"] = p.first;
			break;
		}
	}

    j["is_wall"] = c.is_wall;

	j["destruction_effect"] = c.destruction_effect;
	j["indestructible"] = c.indestructible;

    j["can_open_locks"] = c.can_open_locks;
    j["vibrates"] = c.vibrates;
    j["bonuses_number"] = c.bonuses_number;
    j["attack1_time"] = c.attack1_time;
    j["attack2_time"] = c.attack2_time;
    j["parallax_type"] = c.parallax_type;
    j["transformation"] = c.transformation_str;
    j["bonus"] = c.bonus_str;
    j["ammo1"] = c.ammo1_str;
    j["ammo2"] = c.ammo2_str;
    j["check_tiles"] = c.check_tiles;
    j["sound_frequency"] = c.sound_frequency;
    j["random_sound_frequency"] = c.random_sound_frequency;
    j["is_wall_up"] = c.is_wall_up;
    j["is_wall_down"] = c.is_wall_down;
    j["is_wall_right"] = c.is_wall_right;
    j["is_wall_left"] = c.is_wall_left;

    j["effect"] = c.effect;
    j["is_transparent"] = c.is_transparent;

    j["projectile_charge_time"] = c.projectile_charge_time;

    j["can_glide"] = c.can_glide;
    //j["boss"] = c.boss;
    j["bonus_always"] = c.bonus_always;
    j["can_swim"] = c.can_swim;

	j["always_active"] = c.always_active;

	j["info_id"] = c.info_id;

	if(!c.commands_json.is_null()){
		j["commands"] = c.commands_json;
	}
	if(c.has_dead_weight){
		j["dead_weight"] = c.dead_weight;
	}


	if(c.attack1_offset.has_value()){
		j["attack1_offset"] = *c.attack1_offset;
	}

	if(c.attack2_offset.has_value()){
		j["attack2_offset"] = *c.attack2_offset;
	}
}

}
