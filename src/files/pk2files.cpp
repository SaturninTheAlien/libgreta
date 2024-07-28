#include "pk2files.hpp"
#include <filesystem>
#include <iostream>
#include <algorithm>


namespace fs = std::filesystem;

namespace libgreta{

static fs::path mAssetsPath;

static std::string mEpisodeName;

bool SetAssetsPath(const std::string& name){

    fs::path p = name;

    fs::path p1 = p / "gfx" / "pk2stuff.bmp";

    if(fs::exists(p1)){

        mAssetsPath = p;
        return true;
    }

    fs::path p2 = p / "res" / "gfx" / "pk2stuff.bmp";
    if(fs::exists(p2)){
        mAssetsPath = p / "res";
        return true;
    }

    return false;
}

std::string GetAssetsPath(){
    return mAssetsPath.string();
}

void SetEpisode(const std::string& episodeName){
    mEpisodeName = episodeName;
}

static std::string Lowercase(const std::string& src){

    std::string str = src;

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return str;
}

/**
 * @brief 
 * Finding files, cAsE insensitive
 */
static bool FindFile(const fs::path& dir, const std::string& cAsE, std::string& res){
    if(!fs::exists(dir) || !fs::is_directory(dir))return false;
    std::string name_lowercase = Lowercase(cAsE);

    for (const auto & entry : fs::directory_iterator(dir)){
        if(!entry.is_directory()){
            fs::path filename = entry.path().filename();

            if(name_lowercase == Lowercase(filename.string())){

                res = (dir / filename).string();
                return true;
            }
        }
    }

    return false;
}


bool FindPK2Asset(std::string& name, const std::string& default_dir){
    if(name.empty())return false;

    /**
     * 1. /full_path/pig.spr2
     */
    else if(fs::exists(name) && !fs::is_directory(name))return true;

    std::string filename = fs::path(name).filename();
    if(filename.empty()) return false;

    if(!mEpisodeName.empty()){

        /**
         * @brief 
         * episodes/"episode"/pig.spr2
         */

        if(FindFile(mAssetsPath / "episodes" / mEpisodeName, filename, name))return true;

        /**
         * @brief 
         * episodes/"episode"/sprites/pig.spr2
         */

        if(FindFile(mAssetsPath / "episodes" / mEpisodeName / default_dir, filename, name))return true;
    }

    /**
     * @brief 
     * sprites/pig.spr2
     */

    return FindFile(mAssetsPath / default_dir, filename, name);
}

std::optional<std::string> FindPK2Asset_op(std::string name, const std::string& default_dir){

    if(FindPK2Asset(name, default_dir)){
        return name;
    }
    else{
        return {};
    }
}

}