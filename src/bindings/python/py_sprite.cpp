#include <pybind11/pybind11.h>
#include "sprite/sprite.hpp"
#include "sprite/sprite_io.hpp"
#include <iostream>

namespace py = pybind11;

namespace libgreta{

static std::string Py_ProtoToString(SpritePrototype* proto){
    return std::string("SpritePrototype: \'")+proto->name+"\'";
}

void ExposeSpritePrototype(pybind11::module_ & m){

    py::class_<SpritePrototype>(m, "SpritePrototype")
    .def(py::init<>())
    .def("__str__", &Py_ProtoToString)
    .def_readwrite("name", &SpritePrototype::name)
    .def_readwrite("version", &SpritePrototype::version)
    .def_readwrite("picture", &SpritePrototype::picture_filename)
    .def_readwrite("type", &SpritePrototype::type)
    .def_readwrite("sounds", &SpritePrototype::sounds)
    .def_readwrite("frames_number", &SpritePrototype::frames_number)
    .def_readwrite("frame_rate", &SpritePrototype::frame_rate)
    .def_readwrite("picture_frame_x", &SpritePrototype::picture_frame_x)
    .def_readwrite("picture_frame_y", &SpritePrototype::picture_frame_y)
    .def_readwrite("picture_frame_width", &SpritePrototype::picture_frame_width)
    .def_readwrite("picture_frame_height", &SpritePrototype::picture_frame_height)
    .def_readwrite("width", &SpritePrototype::width)
    .def_readwrite("height", &SpritePrototype::height)
    .def_readwrite("weight", &SpritePrototype::weight)
    .def_readwrite("enemy", &SpritePrototype::enemy)
    .def_readwrite("energy", &SpritePrototype::energy)
    .def_readwrite("damage", &SpritePrototype::damage)
    .def_readwrite("damage_type", &SpritePrototype::damage_type)
    .def_readwrite("immunity_type", &SpritePrototype::immunity_type)
    .def_readwrite("score", &SpritePrototype::score)
    .def_readwrite("ai", &SpritePrototype::AI_v)
    .def_readwrite("max_jump", &SpritePrototype::max_jump)
    .def_readwrite("max_speed", &SpritePrototype::max_speed)
    .def_readwrite("charge_time", &SpritePrototype::charge_time)
    .def_readwrite("color", &SpritePrototype::color)
    .def_readwrite("is_wall", &SpritePrototype::is_wall)
    .def_readwrite("destruction_effect", &SpritePrototype::destruction_effect)
    .def_readwrite("indestructible", &SpritePrototype::indestructible)
    .def_readwrite("can_open_locks", &SpritePrototype::can_open_locks)
    .def_readwrite("vibrates", &SpritePrototype::vibrates)
    .def_readwrite("bonuses_number", &SpritePrototype::bonuses_number)
    .def_readwrite("attack1_time", &SpritePrototype::attack1_time)
    .def_readwrite("attack2_time", &SpritePrototype::attack2_time)
    .def_readwrite("parallax_type", &SpritePrototype::parallax_type)
    .def_readwrite("transformation", &SpritePrototype::transformation_str)
    .def_readwrite("bonus", &SpritePrototype::bonus_str)
    .def_readwrite("ammo1", &SpritePrototype::ammo1_str)
    .def_readwrite("ammo2", &SpritePrototype::ammo2_str)
    .def_readwrite("check_tiles", &SpritePrototype::check_tiles)
    .def_readwrite("sound_frequency", &SpritePrototype::sound_frequency)
    .def_readwrite("random_sound_frequency", &SpritePrototype::random_sound_frequency)
    .def_readwrite("is_wall_up", &SpritePrototype::is_wall_up)
    .def_readwrite("is_wall_down", &SpritePrototype::is_wall_down)
    .def_readwrite("is_wall_right", &SpritePrototype::is_wall_right)
    .def_readwrite("is_wall_left", &SpritePrototype::is_wall_left)
    .def_readwrite("effect", &SpritePrototype::effect)
    .def_readwrite("is_transparent", &SpritePrototype::is_transparent)
    .def_readwrite("projectile_charge_time", &SpritePrototype::projectile_charge_time)
    .def_readwrite("can_glide", &SpritePrototype::can_glide)
    .def_readwrite("bonus_always", &SpritePrototype::bonus_always)
    .def_readwrite("can_swim", &SpritePrototype::can_swim)
    .def_readwrite("info_id", &SpritePrototype::info_id)
    .def_readwrite("always_active", &SpritePrototype::always_active)
    .def_readwrite("has_dead_weight", &SpritePrototype::has_dead_weight)
    .def_readwrite("dead_weight", &SpritePrototype::dead_weight)
    .def_readwrite("attack1_offset", &SpritePrototype::attack1_offset)
    .def_readwrite("attack2_offset", &SpritePrototype::attack2_offset)
    .def_readwrite("player_detection", &SpritePrototype::player_detection)
    .def_readwrite("blend_mode", &SpritePrototype::blend_mode)
    .def_readwrite("blend_alpha", &SpritePrototype::blend_alpha)
    ;

}

void ExposeSpritesIO(pybind11::module_ &m){
    m.def("load_sprite", LoadSprite);
    m.def("load_json_sprite", LoadJsonSprite_s);
    m.def("save_json_sprite", SaveJsonSprite);
    m.def("load_legacy_sprite", LoadLegacySprite_s);
}

}