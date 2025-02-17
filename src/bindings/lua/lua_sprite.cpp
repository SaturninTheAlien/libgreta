#include "lua_sprite.hpp"
#include "../../sprite/sprite.hpp"
#include "../../sprite/sprite_io.hpp"
#include <string>


namespace libgreta{

static std::string Lua_ProtoToString(SpritePrototype* proto){
    return std::string("SpritePrototype: \'")+proto->name+"\'";
}

void ExposeSpritePrototype(sol::table& t){

    t.new_usertype<SpritePrototype>("SpritePrototype",
    "name", &SpritePrototype::name,
    "version", &SpritePrototype::version,


    "picture", &SpritePrototype::picture_filename,
    "type", &SpritePrototype::type,
    "sounds", &SpritePrototype::sounds,
    "frames_number", &SpritePrototype::frames_number,

    //TO DO animations

    "frame_rate", &SpritePrototype::frame_rate,
    "picture_frame_x", &SpritePrototype::picture_frame_x,
    "picture_frame_y", &SpritePrototype::picture_frame_y,
    "picture_frame_width", &SpritePrototype::picture_frame_width,
    "picture_frame_height", &SpritePrototype::picture_frame_height,
    "width", &SpritePrototype::width,
    "height", &SpritePrototype::height,
    "weight", &SpritePrototype::weight,

    "enemy", &SpritePrototype::enemy,
    "energy", &SpritePrototype::energy,
    "damage", &SpritePrototype::damage,
    "damage_type", &SpritePrototype::damage_type,
    "immunity_type", &SpritePrototype::immunity_type,
    "score", &SpritePrototype::score,

    "ai", &SpritePrototype::AI_v,
    "max_jump", &SpritePrototype::max_jump,
    "max_speed", &SpritePrototype::max_speed,
    "charge_time", &SpritePrototype::charge_time,
    "color", &SpritePrototype::color,
    "is_wall", &SpritePrototype::is_wall,

    "destruction_effect", &SpritePrototype::destruction_effect,
    "indestructible", &SpritePrototype::indestructible,

    "can_open_locks", &SpritePrototype::can_open_locks,
    "vibrates", &SpritePrototype::vibrates,

    "bonuses_number", &SpritePrototype::bonuses_number,

    "attack1_time", &SpritePrototype::attack1_time,
    "attack2_time", &SpritePrototype::attack2_time,

    "parallax_type", &SpritePrototype::parallax_type,

    "transformation", &SpritePrototype::transformation_str,
    "bonus", &SpritePrototype::bonus_str,
    "ammo1", &SpritePrototype::ammo1_str,
    "ammo2", &SpritePrototype::ammo2_str,

    "check_tiles", &SpritePrototype::check_tiles,
    "sound_frequency", &SpritePrototype::sound_frequency,
    "random_sound_frequency", &SpritePrototype::random_sound_frequency,

    "is_wall_up", &SpritePrototype::is_wall_up,
    "is_wall_down", &SpritePrototype::is_wall_down,
    "is_wall_right", &SpritePrototype::is_wall_right,
    "is_wall_left", &SpritePrototype::is_wall_left,

    "effect", &SpritePrototype::effect,
    "is_transparent", &SpritePrototype::is_transparent,
    "projectile_charge_time", &SpritePrototype::projectile_charge_time,
    "can_glide", &SpritePrototype::can_glide,
    "bonus_always", &SpritePrototype::bonus_always,
    "can_swim", &SpritePrototype::can_swim,
    "info_id", &SpritePrototype::info_id,
    "always_active", &SpritePrototype::always_active,
    "has_dead_weight", &SpritePrototype::has_dead_weight,
    "dead_weight", &SpritePrototype::dead_weight,
    "attack1_offset", &SpritePrototype::attack1_offset,
    "attack2_offset", &SpritePrototype::attack2_offset,
    "__tostring", Lua_ProtoToString);
}

void ExposeSpritesIO(sol::table& t){
    t["LoadSprite"] = LoadSprite;
    t["LoadJsonSprite"] = LoadJsonSprite_s;
    t["SaveJsonSprite"] = SaveJsonSprite;
    t["LoadLegacySprite"] = LoadLegacySprite_s;
}

}