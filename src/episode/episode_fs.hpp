#pragma once
#include <string>
#include <optional>
#include <filesystem>
#include "utils/api.hpp"

#include "utils/file.hpp"

namespace libgreta{

extern GRETA_API const std::string EPISODES_DIR;

extern GRETA_API const std::string GFX_DIR;
extern GRETA_API const std::string TILES_DIR;
extern GRETA_API const std::string SCENERY_DIR;

extern GRETA_API const std::string LANGUAGE_DIR;
extern GRETA_API const std::string FONTS_DIR;

extern GRETA_API const std::string SFX_DIR;
extern GRETA_API const std::string SPRITES_DIR;
extern GRETA_API const std::string MUSIC_DIR;

extern GRETA_API const std::string LUA_DIR;
extern GRETA_API const std::string LIFE_DIR;


enum{
    ASSET_EPISODE_ROOT = -1,
    ASSET_UNKNOWN = 0,
    ASSET_LEVEL = 1,
    ASSET_SPRITE = 2,
    ASSET_SPRITE_TEXTURE = 3,
    ASSET_SPRITE_SOUND = 4,
    ASSET_TILESET = 5,
    ASSET_SCENERY = 6,
    ASSET_LUA = 7,
    ASSET_GFX = 8
};

const std::string& GRETA_API getDefaultDirForAssetType(int type);

class PZip;

class GRETA_API EpisodeFS{
public:
    EpisodeFS() = default;
    EpisodeFS(const std::string& assetsPath, const std::string& episodePath);
    EpisodeFS(const std::string& assetsPath,
        const std::string& episodeName,
        PZip * zipFile);

    virtual ~EpisodeFS(){};

    std::string getAssetsPath(){
        return this->assetsPath.string();
    }
    std::string getEpisodePath(){
        return this->episodePath.string();
    }

    std::string getEpisodeName()const{
        return this->episodePath.filename().string();
    }

    void setAssetsPath(const std::string& path);
    void setEpisode(const std::string& path, PZip* zip);
    
    std::optional<File> findAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const;

    std::vector<File> searchForLevels();
protected:
    std::optional<File> findVanillaAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const;

    std::optional<File> findEpisodeAsset(const std::string& name,
        const std::string& default_dir,
        const std::string& alt_extension)const;

private:
    std::filesystem::path assetsPath;
    std::filesystem::path episodePath;

    PZip * zip = nullptr;
};

}