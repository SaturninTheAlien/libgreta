#include "lua_files.hpp"

#include "utils/file.hpp"
#include <optional>

namespace libgreta{

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
    sol::constructors<File(const std::string&)>(),
    "isZip", &File::isZip,
    "getFilename", &File::getFilename,
    "getExtension", &File::getExtension,
    "getContent", &File::getContent,
    "getContentAsString", &File::getContentAsString,
    "__tostring", Lua_FileToStr);

    t["ScanDir"] = ScanDir;
}

}