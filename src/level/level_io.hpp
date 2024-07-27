#pragma once
#include <string>

#include "utils/api.hpp"

namespace libgreta{

class Level;

GRETA_API Level LoadLevel(const std::string& filename);
GRETA_API void SaveLevel(const Level& level, const std::string& filename);

}