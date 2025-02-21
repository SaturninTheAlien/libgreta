#include "pk2filesystem.hpp"
#include <filesystem>
#include "utils/zip_utils.hpp"
#include "utils/string_utils.hpp"

//#include <iostream>

namespace fs = std::filesystem;

namespace libgreta{

const std::string EPISODES_DIR = "episodes";
const std::string GFX_DIR = "gfx";

const std::string TILES_DIR = (fs::path(GFX_DIR) / "tiles").string();
const std::string SCENERY_DIR = (fs::path(GFX_DIR) / "scenery").string();

const std::string LANGUAGE_DIR = "language";
const std::string FONTS_DIR = (fs::path(LANGUAGE_DIR) / "fonts").string();

const std::string SFX_DIR = "sfx";
const std::string SPRITES_DIR = "sprites";
const std::string MUSIC_DIR = "music";

const std::string LUA_DIR = "lua";
const std::string LIFE_DIR = "rle";

static fs::path mAssetsPath;
static fs::path mEpisodePath;
static PZip* mEpisodeZip;

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

void SetEpisode(const std::string& episodeName, PZip* zip_file){
    mEpisodeZip = zip_file;
    if(zip_file==nullptr){
        mEpisodePath = episodeName;
        if(!mEpisodePath.is_absolute()){
            mEpisodePath = mAssetsPath / "episodes" / mEpisodePath;
        }
    }
    else{
        mEpisodePath = fs::path("episodes") / episodeName;
    }
}


/**
 * @brief 
 * Finding files, cAsE insensitive
 */
static std::optional<std::string> FindFile(const fs::path& dir, const std::string& cAsE,  const std::string& alt_extension){
    if(!fs::exists(dir) || !fs::is_directory(dir))return {};
    std::string name_lowercase = PString::rtrim( PString::lowercase(cAsE));

    std::string name_lowercase_alt = "";
    if(!alt_extension.empty()){
        name_lowercase_alt = fs::path(name_lowercase).replace_extension(alt_extension).string();
    }

    std::optional<std::string> alt_res = {};


    for (const auto & entry : fs::directory_iterator(dir)){
        if(!entry.is_directory()){
            fs::path filename = entry.path().filename();

            std::string s1 = PString::lowercase(filename.string());
            
            if(name_lowercase == s1){

                return (dir / filename).string();
            }
            else if(!alt_extension.empty() && name_lowercase_alt == s1){
                alt_res = (dir / filename).string();

            }
        }
    }

    return alt_res;
}






std::optional<File> FindVanillaAsset(const std::string& name, const std::string& default_dir, const std::string& alt_extension){
    std::string filename = fs::path(name).filename().string();
    /**
     * @brief 
     * sprites/pig.spr2
     */
    std::optional<std::string> op = FindFile(mAssetsPath / default_dir, filename, alt_extension);
    if(op.has_value()){
        return File(*op);
    }
    return {};
}



std::optional<File> FindEpisodeAsset(const std::string& name, const std::string& default_dir, const std::string& alt_extension){
    std::string filename = fs::path(name).filename().string();
    if(filename.empty()) return {};

    if(mEpisodeZip!=nullptr){

        std::optional<PZipEntry> entry;
        /**
         * @brief 
         * zip:/episodes/"episode"/pig.spr2
         */

        entry = mEpisodeZip->getEntry( (mEpisodePath / filename).string(), alt_extension);
        if(entry.has_value())return File(mEpisodeZip, *entry);
        
        /**
         * @brief 
         * zip:/sprites/pig.spr2
         */
        if(!default_dir.empty()){
            entry = mEpisodeZip->getEntry((fs::path(default_dir)/filename).string(), alt_extension);
            if(entry.has_value())return File(mEpisodeZip, *entry);
        }

        
    }
    
    else if(!mEpisodePath.empty()){
        /**
         * @brief 
         * episodes/"episode"/pig.spr2
         */
        std::optional<std::string> op = FindFile(mEpisodePath, filename, alt_extension);
        if(op.has_value()){
            return File(*op);
        }

        /**
         * @brief 
         * episodes/"episode"/sprites/pig.spr2
         */
        if(!default_dir.empty()){
            op = FindFile(mEpisodePath / default_dir, filename, alt_extension);
            if(op.has_value()){
                return File(*op);
            }
        }
    }

    return {};
}

std::optional<File> FindAsset(const std::string& name, const std::string& default_dir, const std::string& alt_extension){
    if(name.empty())return {};

    /**
     * 1. /full_path/pig.spr2
     */    
    fs::path p(name);
    if(p.is_absolute() && fs::exists(p) && !fs::is_directory(p))return File(name);

    std::optional<File> op = FindEpisodeAsset(name, default_dir, alt_extension);
    if(op.has_value())return op;

    op = FindVanillaAsset(name, default_dir, alt_extension);
    
    /*if(!op.has_value()){
        PLog::Write(PLog::WARN, "PFilesystem", "File \"%s\" not found!", name.c_str());
    }*/

    return op;
}

std::vector<File> SearchForLevels(){
    std::vector<File> levels;
    if(mEpisodeZip!=nullptr){
        throw std::runtime_error("Zips not supported yet!");
    }

    //std::cout<<mEpisodePath<<std::endl;

    for(const auto& entry: fs::directory_iterator(mEpisodePath)){

        //std::cout<<entry.path()<<std::endl;

        if(!entry.is_directory()){
            std::string extension = entry.path().extension().string();
            if(extension==".map"){
                levels.emplace_back(File(entry.path().string()));
            }            
        }
    }
    return levels;
}

}
