#include <pybind11/stl.h>
#include "py_episode.hpp"

#include "episode/episode.hpp"
#include <string>

namespace libgreta{

void ExposeEpisode(pybind11::module_ & m){

    pybind11::class_<Asset>(m, "Asset")
    .def_readonly("filename", &Asset::filename)
    .def_readonly("type", &Asset::type)
    .def_readonly("parent", &Asset::parent)
    .def("get_stack_trace", &Asset::getStackTrace)
    .def("__str__", &Asset::str);

    pybind11::class_<MissingAsset>(m, "MissingAsset")
    .def("__str__", &MissingAsset::str);

    pybind11::class_<MalformedAsset>(m, "MalformedAsset")
    .def("__str__", &MalformedAsset::str)
    .def_readonly("what", &MalformedAsset::what);

    pybind11::class_<SpriteAsset>(m, "SpriteAsset")
    .def_readwrite("prototype", &SpriteAsset::prototype)
    .def_readwrite("bonus", &SpriteAsset::bonus)
    .def_readwrite("ammo1", &SpriteAsset::ammo1)
    .def_readwrite("ammo2", &SpriteAsset::ammo2)
    .def_readwrite("transformation", &SpriteAsset::transformation);

    pybind11::class_<EpisodeFS>(m, "EpisodeFS")
    .def(pybind11::init<const std::string&, const std::string&, PZip*>())
    .def(pybind11::init<const std::string&, const std::string&>())
    .def("set_episode", &EpisodeFS::setEpisode)
    .def("get_assets_path", &EpisodeFS::getAssetsPath)
    .def("get_episode_path", &EpisodeFS::getEpisodePath)
    .def("get_episode_name", &EpisodeFS::getEpisodeName)
    .def("find_asset", &EpisodeFS::findAsset)
    .def("search_for_levels", &EpisodeFS::searchForLevels);

    /*pybind11::class_<EpisodeTree>(m, "EpisodeTree")
    .def(pybind11::init<const std::string&, const std::string&, PZip*>())
    .def(pybind11::init<const std::string&, const std::string&>())
    .def("load_sprite", &EpisodeTree::loadSprite)
    .def("debug", &EpisodeTree::debug)
    .def("load_level", &EpisodeTree::loadLevel)
    .def("load_all_levels", &EpisodeTree::loadAllLevels)
    .def("get_missing_assets", &EpisodeTree::getMissingAssets)
    .def("get_malformed_assets", &EpisodeTree::getMalformedAssets);*/

    m.def("get_dir_for_asset_type", getDefaultDirForAssetType);
}

}