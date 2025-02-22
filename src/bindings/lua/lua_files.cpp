#include "lua_files.hpp"

#include "utils/file.hpp"
#include <optional>
#include <filesystem>

namespace libgreta{

static std::string Lua_FileToStr(File* file){
    if(file->isZip()){
        return std::string("zip:/") + file->str();   
    }
    else{
        return file->str();
    }
}

static bool Lua_IsAbsolute(const std::string& s){
    return std::filesystem::path(s).is_absolute();
}

static bool Lua_Exists(const std::string& s){
    return std::filesystem::exists(s);
}

static bool Lua_IsDir(const std::string& s){
    return std::filesystem::is_directory(s);
}


void ExposeFileClass(sol::table& t){
    t.new_usertype<File>("File",
    sol::constructors<File(const std::string&)>(),
    "isZip", &File::isZip,
    "getFilename", &File::getFilename,
    "getExtension", &File::getExtension,
    "getContent", &File::getContent,
    "getContentAsString", &File::getContentAsString,
    "__tostring", Lua_FileToStr);
}


void ExposeFilesystemAPI(sol::table& t){

    t["exits"] = Lua_Exists;
    t["scan_dir"] = ScanDir;
    t["is_absolute"] = Lua_IsAbsolute;
    t["is_directory"] = Lua_IsDir;
}

}