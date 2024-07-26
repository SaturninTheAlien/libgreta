#pragma once

#include <vector>
#include <string>
#include <map>

#include "sprite_constants.hpp"
#include "utils/api.hpp"
#include "utils/types.hpp"
#include "3rd_party/json.hpp"

#define SPRITE_ANIMATIONS_NUMBER       11
#define SPRITE_SOUNDS_NUMBER     7

namespace libgreta{

/**
 * @brief 
 * Legacy classes declaration
 */
struct LegacySprAnimation;
struct PrototypeClass10;
struct PrototypeClass11;
struct PrototypeClass12;
struct PrototypeClass13;

class GRETA_API SpriteAnimation{
public:
    SpriteAnimation(){};
    SpriteAnimation(const LegacySprAnimation& anim);
    bool loop = false;
    u32 intro = 0;

    std::vector<int> sequence;

    friend void to_json(nlohmann::json& j, const SpriteAnimation& a);
    friend void from_json(const nlohmann::json&j, SpriteAnimation& a);
};

class GRETA_API SpritePrototype{
public:
    SpritePrototype()=default;
    ~SpritePrototype()=default;

    SpritePrototype(const nlohmann::json& j);

    /**
     * @brief Legacy sprite formats
     */
    SpritePrototype(PrototypeClass10 &proto);
    SpritePrototype(PrototypeClass11 &proto);
    SpritePrototype(PrototypeClass12 &proto);
    SpritePrototype(PrototypeClass13 &proto);   

    friend void to_json(nlohmann::json& j, const SpritePrototype& c); 

    static const std::map<std::string, int> SoundTypesDict;
    static const std::map<std::string, int> AnimationsDict;
    static const std::map<std::string, u8> ColorsDict;

    std::string version = "2.0";

    std::string filename;
    std::string picture_filename;
    
    int     type = TYPE_NOTHING;

    std::array<std::string, SPRITE_SOUNDS_NUMBER> sound_files = {""};
    std::array<int, SPRITE_SOUNDS_NUMBER> sounds = {-1};

    int      frames_number            = 0;

    std::array<SpriteAnimation, SPRITE_ANIMATIONS_NUMBER> animations;

    int      frame_rate         = 0;
    int     picture_frame_x             = 0;
    int     picture_frame_y             = 0;
    int     picture_frame_width  = 0;
    int     picture_frame_height = 0;

    std::string name;
    int     width    = 0;
    int     height   = 0;
    double  weight    = 0;

    bool    enemy     = false;

    int     energy        = 0;
    int     damage        = 0;
    int      damage_type = DAMAGE_IMPACT;
    int      immunity_type        = DAMAGE_NONE;
    int     score        = 0;

    std::vector<int> AI_v;

    int      max_jump    = 0;
    double  max_speed   = 3;
    int     charge_time  = 0;
    u8      color         = COLOR_NORMAL;
    bool    is_wall         = false;
    
    int     destruction_effect = FX_DESTRUCT_NO_EFFECT;
    bool    indestructible = false; //if true only DAMAGE_ALL can really hurt the sprite  
    
    bool    can_open_locks        = false;
    bool    vibrates      = false;
    int      bonuses_number = 1;
    int     attack1_time = 60;
    int     attack2_time = 60;

    int     parallax_type = 0;

    std::string transformation_str;
    std::string bonus_str;
    std::string ammo1_str;
    std::string ammo2_str;


    /*SpritePrototype* transformation     = nullptr;
    SpritePrototype* bonus      = nullptr;
    SpritePrototype* ammo1     = nullptr;
    SpritePrototype* ammo2     = nullptr;*/

    bool    check_tiles = true;
    int     sound_frequency      = 22050;
    bool    random_sound_frequency    = true;

    bool    is_wall_up       = true;
    bool    is_wall_down       = true;
    bool    is_wall_right   = true;
    bool    is_wall_left = true;

    u8      effect       = EFFECT_NONE;
    bool    is_transparent       = false;
    int     projectile_charge_time    = 0;
    bool    can_glide    = false;
    bool    bonus_always = false;
    bool    can_swim     = false;

    /**
     * @brief 
     * The ID of displayed text in the "shoutbox"
     */
    int     info_id = 0;

    /**
     * @brief 
     * If true a sprite will be active even far from the camera
     */
    bool    always_active = false;   // 


    /**
     * @brief 
     * Weight when KO'd variable
     * If has_dead_weight set to false, to legacy behaviour
     * (only sprites with weight 0 fall) 
     */
    
    bool has_dead_weight = false;
    double  dead_weight = 0;

    //SpritePrototype()=default;
    //~SpritePrototype()=default;

private:
    nlohmann::json commands_json;
       
};

}