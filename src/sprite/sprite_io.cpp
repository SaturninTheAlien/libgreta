#include "sprite_io.hpp"
#include <fstream>
#include <stdexcept>

namespace libgreta{

void SaveSprite(const SpritePrototype& prototype, const std::string& filename){
    std::ofstream f(filename.c_str());

    if(!f.good()){
        throw std::runtime_error("Unable to save sprite!");
    }

    nlohmann::json j(prototype);
    f<<j.dump(4)<<std::endl;
    f.close();
}

SpritePrototype LoadJsonSprite(const std::string& filename){
    std::ifstream f(filename);

    if(!f.good()){
        throw std::runtime_error("Cannot load sprite!");
    }

    nlohmann::json j;
    f>>j;
    f.close();
    
    return SpritePrototype(j);
}

}