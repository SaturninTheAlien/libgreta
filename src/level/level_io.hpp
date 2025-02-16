#pragma once
#include <string>

#include "utils/api.hpp"
#include "files/pk2file.hpp"

namespace libgreta{

class Level;

GRETA_API Level LoadLevel(const File& file);
GRETA_API Level LoadLevel_s(const std::string& filename);
GRETA_API void SaveLevel_s(const Level& level, const std::string& filename);

}