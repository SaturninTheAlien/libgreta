#pragma once
#include "sprite.hpp"
#include "utils/api.hpp"

namespace libgreta{

GRETA_API void SaveJsonSprite(const SpritePrototype& prototype, const std::string& filename);
GRETA_API SpritePrototype LoadJsonSprite(const std::string& filename);
GRETA_API SpritePrototype LoadLegacySprite(const std::string& filename);

}