#pragma once
#include <string>
#include <istream>

#include "utils/api.hpp"
#include "utils/zip_utils.hpp"
#include "utils/json_utils.hpp"

namespace libgreta{

GRETA_API void panicWhenFileNotFound(const std::string& path);

GRETA_API class File {
public:
    File(std::string path):
    path(path){
    
    }

    File(PZip* zip_file, const PZipEntry&e):
    path(e.name), zip_file(zip_file), zip_entry(e){

    }

    bool operator ==(const File& file)const;
    const char* c_str()const{
        return this->path.c_str();
    }

    const std::string& str()const{
        return this->path;
    }

    bool isZip()const{
        return this->zip_file!=nullptr;
    }

    std::string getFilename()const;
    std::string getExtension()const;

    nlohmann::json getContentAsJSON()const;
    std::string getContentAsString()const;
    std::vector<char> getContent()const;

#ifdef __ANDROID__
    bool insideAndroidAPK = false;
#endif

private:
    std::string path;
    PZip* zip_file = nullptr;
    PZipEntry zip_entry;
};

std::vector<File> ScanDir(const std::string& dir, const std::string& filter);

}