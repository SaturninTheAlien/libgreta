#pragma once
#include "sprite.hpp"
#include "utils/api.hpp"
#include "files/pk2file.hpp"

namespace libgreta{

GRETA_API void SaveJsonSprite(const SpritePrototype& prototype, const std::string& filename);

GRETA_API SpritePrototype LoadSprite(const File& file);

GRETA_API SpritePrototype LoadJsonSprite_s(const std::string& filename);
GRETA_API SpritePrototype LoadLegacySprite_s(const std::string& filename);

}