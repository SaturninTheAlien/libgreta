#include "lua_episode.hpp"
#include "episode/episode.hpp"
#include <string>

namespace libgreta{

void ExposeEpisode(sol::table& t){

    t.new_usertype<Asset>("Asset",
    sol::no_constructor,
    "filename", sol::readonly(&Asset::filename),
    "type",  sol::readonly(&Asset::type),
    "parent", sol::readonly(&Asset::parent),
    "getStackTrace", &Asset::getStackTrace,
    "__tostring", &Asset::str);

    t.new_usertype<MissingAsset>("MissingAsset",
        sol::no_constructor,
        "__tostring", &MissingAsset::str,
        sol::base_classes, sol::bases<Asset>()
    );

    t.new_usertype<MalformedAsset>("MissingAsset",
        sol::no_constructor,
        "what", sol::readonly(&MalformedAsset::what),
        "__tostring", &MalformedAsset::str,
        sol::base_classes, sol::bases<Asset>()
    );

    t.new_usertype<SpriteAsset>("SpriteAsset",
        "prototype", &SpriteAsset::prototype,
        "bonus", &SpriteAsset::bonus,
        "ammo1", &SpriteAsset::ammo1,
        "ammo1", &SpriteAsset::ammo2,
        "transformation",&SpriteAsset::transformation,
        //"__tostring", &SpriteAsset::str,
        sol::base_classes, sol::bases<Asset>()
    );

    

    t.new_usertype<EpisodeFS>("EpisodeFS",
        sol::constructors<
        EpisodeFS(const std::string&, const std::string&, PZip*),
        EpisodeFS(const std::string&, const std::string&)>(),


        "setEpisode", &EpisodeFS::setEpisode,
        "getAssetsPath", &EpisodeFS::getAssetsPath,
        "getEpisodePath", &EpisodeFS::getEpisodePath,
        "getEpisodeName", &EpisodeFS::getEpisodeName,

        "findAsset", &EpisodeFS::findAsset,
        "searchForLevels", &EpisodeFS::searchForLevels
    );


    t.new_usertype<EpisodeTree>("EpisodeTree",
    sol::constructors<
        EpisodeTree(const std::string&, const std::string&, PZip*),
        EpisodeTree(const std::string&, const std::string&)>(),
        "loadSprite", &EpisodeTree::loadSprite,
        "debug", &EpisodeTree::debug,
        "loadLevel", &EpisodeTree::loadLevel,
        "loadAllLevels", &EpisodeTree::loadAllLevels,

        "getMissingAssets", &EpisodeTree::getMissingAssets,
        "getMalformedAssets", &EpisodeTree::getMalformedAssets,

        sol::base_classes, sol::bases<EpisodeFS>()
    );
}

}