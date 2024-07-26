#include "lua_sprite.hpp"
#include "sprite.hpp"
#include "sprite_io.hpp"

namespace libgreta{

void ExposeSpritePrototype(sol::table& t){

    t.new_usertype<SpritePrototype>("SpritePrototype",
    "name", &SpritePrototype::name,
    "filename", &SpritePrototype::filename,
    "version", &SpritePrototype::version,


    "picture", &SpritePrototype::picture_filename,
    "type", &SpritePrototype::type,
    "sounds", &SpritePrototype::sounds,
    "frames_number", &SpritePrototype::frames_number);

}

}