#pragma once
#include <string>
#include "utils/api.hpp"
#include <optional>

namespace libgreta{

GRETA_API bool SetAssetsPath(const std::string& name);

GRETA_API std::string GetAssetsPath();

GRETA_API void SetEpisode(const std::string& episodeName);

bool GRETA_API FindPK2Asset(std::string& name, const std::string& default_dir);
std::optional<std::string> FindPK2Asset_op(std::string name, const std::string& default_dir);

}