#include "lua_episode.hpp"
#include "episode/episode.hpp"
#include <string>

namespace libgreta{

static std::string Lua_SpriteNodeStr(SpriteNode* node){  
    return std::string("SpriteNode: \'")+node->filename+"\'";
}

static void Lua_EpisodeCheckLevel(Episode* episode, const Level& level){
    if(episode==nullptr)return;

    episode->checkLevel(level, nullptr);
}

void ExposeEpisode(sol::table& t){
    t.new_usertype<SpriteNode>("SpriteNode",
    sol::no_constructor,
    "filename",  &SpriteNode::filename,
    "prototype", &SpriteNode::prototype,
    "bonus", &SpriteNode::bonus,
    "ammo1", &SpriteNode::ammo1,
    "ammo1", &SpriteNode::ammo2,
    "transformation",&SpriteNode::transformation,
    "__tostring", Lua_SpriteNodeStr);


    t.new_usertype<Episode>("Episode",
    "loadSprite", &Episode::loadSprite,
    "verbose", &Episode::verbose,
    "loadLevel", &Episode::loadLevel,
    "checkLevel", Lua_EpisodeCheckLevel);
}

}