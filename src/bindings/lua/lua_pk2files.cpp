#include "lua_pk2files.hpp"

#include "files/pk2file.hpp"
#include "files/pk2filesystem.hpp"
#include <optional>

namespace libgreta{

static std::optional<File> Lua_FindAsset1(
    const std::string& name,
    const std::string& default_dir){

    return FindAsset(name, default_dir, "");
}

static std::string Lua_FileToStr(File* file){
    if(file->isZip()){
        return std::string("zip:/") + file->str();   
    }
    else{
        return file->str();
    }
}

void ExposePK2FilesApi(sol::table& t){

    t.new_usertype<File>("File",
    "isZip", &File::isZip,
    "getFilename", &File::getFilename,
    "getExtension", &File::getExtension,
    "getContent", &File::getContent,
    "getContentAsString", &File::getContentAsString,
    "__tostring", Lua_FileToStr);

    t["SetAssetsPath"] = SetAssetsPath;
    t["GetAssetsPath"] = GetAssetsPath;

    t["SetEpisode"] = SetEpisode;
    t["FindAsset"] = sol::overload(FindAsset, Lua_FindAsset1);
}

}