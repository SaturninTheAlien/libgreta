#include <stdexcept>
#include <sstream>
#include "episode_fs.hpp"
#include <filesystem>
#include "utils/zip_utils.hpp"
#include "utils/string_utils.hpp"

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


const std::string& getDefaultDirForAssetType(int type){
    switch (type)
    {
    case ASSET_EPISODE_ROOT:
    case ASSET_UNKNOWN:
    case ASSET_LEVEL:
        return EPISODES_DIR;

    case ASSET_SPRITE:
    case ASSET_SPRITE_TEXTURE:
    case ASSET_SPRITE_SOUND:
        return SPRITES_DIR;

    case ASSET_TILESET:
        return TILES_DIR;

    case ASSET_SCENERY:
        return SCENERY_DIR;
    case ASSET_LUA:
        return LUA_DIR;
    case ASSET_GFX:
        return GFX_DIR;
        
    default:
        break;
        
    }

    return EPISODES_DIR;
}


static fs::path _fixAssetsPath(const std::string & name){
    fs::path p = name;
    fs::path p1 = p / "gfx" / "pk2stuff.bmp";

    if(fs::exists(p1)){

        return p;
    }
    p1 = p / "gfx" / "pk2stuff.png";
    if(fs::exists(p1)){

        return p;
    }

    fs::path p2 = p / "res" / "gfx" / "pk2stuff.bmp";
    fs::path p3 = p / "res" / "gfx" / "pk2stuff.png";

    if(fs::exists(p2) || fs::exists(p3) ){
        return p / "res";
    }

    std::ostringstream os;
    os<< "Incorrect assets path: "<<name<<std::endl;
    throw std::runtime_error(os.str());
}


EpisodeFS::EpisodeFS(const std::string& assetsPath, const std::string& episodePath)
:assetsPath(_fixAssetsPath(assetsPath)), episodePath(fs::path(episodePath)){
    if(!this->episodePath.is_absolute()){
        this->episodePath = this->assetsPath / "episodes" / this->episodePath;
    }
}

EpisodeFS::EpisodeFS(const std::string& assetsPath, const std::string& episodeName, PZip* zip)
:assetsPath(_fixAssetsPath(assetsPath)), episodePath(episodeName), zip(zip) {
    if(zip==nullptr){
        if(!this->episodePath.is_absolute()){
            this->episodePath = this->assetsPath / "episodes" / this->episodePath;
        }
    }
    else{
        this->episodePath = fs::path("episodes") / this->episodePath;
    }
}


void EpisodeFS::setEpisode(const std::string& path, PZip* zip){
    this->episodePath = path;
    this->zip = zip;

    if(zip==nullptr){
        if(!this->episodePath.is_absolute()){
            this->episodePath = this->assetsPath / "episodes" / this->episodePath;
        }
    }
    else{
        this->episodePath = fs::path("episodes") / this->episodePath;
    }
}

void EpisodeFS::setAssetsPath(const std::string& path){
    this->assetsPath = _fixAssetsPath(path);
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






std::optional<File> EpisodeFS::findVanillaAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const{

    std::string filename = fs::path(name).filename().string();
    /**
     * @brief 
     * sprites/pig.spr2
     */
    std::optional<std::string> op = FindFile(this->assetsPath / default_dir, filename, alt_extension);
    if(op.has_value()){
        return File(*op);
    }
    return {};
}



std::optional<File> EpisodeFS::findEpisodeAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const{

    std::string filename = fs::path(name).filename().string();
    if(filename.empty()) return {};

    if(this->zip!=nullptr){

        std::optional<PZipEntry> entry;
        /**
         * @brief 
         * zip:/episodes/"episode"/pig.spr2
         */

        entry = zip->getEntry( (this->episodePath / filename).string(), alt_extension);
        if(entry.has_value())return File(zip, *entry);
        
        /**
         * @brief 
         * zip:/sprites/pig.spr2
         */
        if(!default_dir.empty()){
            entry = zip->getEntry((fs::path(default_dir)/filename).string(), alt_extension);
            if(entry.has_value())return File(zip, *entry);
        }

        
    }
    
    else if(! this->episodePath.empty()){
        /**
         * @brief 
         * episodes/"episode"/pig.spr2
         */
        std::optional<std::string> op = FindFile(this->episodePath, filename, alt_extension);
        if(op.has_value()){
            return File(*op);
        }

        /**
         * @brief 
         * episodes/"episode"/sprites/pig.spr2
         */
        if(!default_dir.empty()){
            op = FindFile(this->episodePath / default_dir, filename, alt_extension);
            if(op.has_value()){
                return File(*op);
            }
        }
    }

    return {};
}

std::optional<File> EpisodeFS::findAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const{

    if(name.empty())return {};

    /**
     * 1. /full_path/pig.spr2
     */    
    fs::path p(name);
    if(p.is_absolute() && fs::exists(p) && !fs::is_directory(p))return File(name);

    std::optional<File> op = this->findEpisodeAsset(name, default_dir, alt_extension);
    if(op.has_value())return op;

    op = this->findVanillaAsset(name, default_dir, alt_extension);
    
    /*if(!op.has_value()){
        PLog::Write(PLog::WARN, "PFilesystem", "File \"%s\" not found!", name.c_str());
    }*/

    return op;
}

std::vector<File> EpisodeFS::searchForLevels(){
    std::vector<File> levels;
    if(this->zip!=nullptr){
        std::vector<PZipEntry> entries = this->zip->scanDirectory(this->episodePath.string(), ".map");
        for(const PZipEntry& entry: entries){

            levels.emplace_back(File(this->zip, entry));

        }
    }
    else{
        for(const auto& entry: fs::directory_iterator(this->episodePath)){
            if(!entry.is_directory()){
                std::string extension = entry.path().extension().string();
                if(extension==".map"){
                    levels.emplace_back(File(entry.path().string()));
                }            
            }
        }

    }
    return levels;
}

}
