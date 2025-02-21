#include "lua_crawler.hpp"
#include "crawler/crawler.hpp"
#include <string>

namespace libgreta{

static std::string Lua_SpriteNodeStr(SpriteNode* node){  
    return std::string("SpriteNode: \'")+node->filename+"\'";
}

static void Lua_CrawlerCheckLevel(PK2Crawler* crawler, const Level& level){
    if(crawler==nullptr)return;

    crawler->checkLevel(level, nullptr);
}

void ExposeCrawler(sol::table& t){
    t.new_usertype<SpriteNode>("SpriteNode",
    sol::no_constructor,
    "filename",  &SpriteNode::filename,
    "prototype", &SpriteNode::prototype,
    "bonus", &SpriteNode::bonus,
    "ammo1", &SpriteNode::ammo1,
    "ammo1", &SpriteNode::ammo2,
    "transformation",&SpriteNode::transformation,
    "__tostring", Lua_SpriteNodeStr);


    t.new_usertype<PK2Crawler>("Crawler",
    "loadSprite", &PK2Crawler::loadSprite,
    "verbose", &PK2Crawler::verbose,
    "loadLevel", &PK2Crawler::loadLevel,
    "checkLevel", Lua_CrawlerCheckLevel);
}

}