#pragma once
#include <string>
#include <optional>
#include <filesystem>
#include "utils/api.hpp"

#include "pk2file.hpp"

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

GRETA_API bool SetAssetsPath(const std::string& name);
GRETA_API std::string GetAssetsPath();
GRETA_API void SetEpisode(const std::string& episodeName, PZip* zip_file);


GRETA_API std::vector<File> SearchForZips();
GRETA_API std::vector<File> SearchForLevels();

GRETA_API std::optional<File> FindAsset(
    const std::string& name,
    const std::string& default_dir,
    const std::string& alt_extension="");
}