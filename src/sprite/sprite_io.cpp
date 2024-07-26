#include "sprite_io.hpp"
#include "sprite_legacy.hpp"
#include <fstream>
#include <stdexcept>

namespace libgreta{

void SaveJsonSprite(const SpritePrototype& prototype, const std::string& filename){
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
        throw std::runtime_error("Cannot open a file: "+filename);
    }

    nlohmann::json j;
    f>>j;
    f.close();
    
    return SpritePrototype(j);
}

SpritePrototype LoadLegacySprite(const std::string& filename){
    std::ifstream f(filename, std::ios::binary);
    if(!f.good()){
        throw std::runtime_error("Cannot open a file: "+filename);
    }

    char version[4];
    f.read(version, 4);
    if (strcmp(version,"1.3") == 0){
        PrototypeClass13 sprite13;        
        f.read((char*)&sprite13, sizeof(PrototypeClass13));
        return SpritePrototype(sprite13);        
    }
    else if(strcmp(version,"1.2") == 0){
        PrototypeClass12 sprite12;        
        f.read((char*)&sprite12, sizeof(PrototypeClass12));
        return SpritePrototype(sprite12);  

    }
    else if(strcmp(version,"1.1") == 0){
        PrototypeClass11 sprite11;
        f.read((char*)&sprite11, sizeof(PrototypeClass11));
        return SpritePrototype(sprite11);

    }
    else if(strcmp(version,"1.0") == 0){
        PrototypeClass10 sprite10;        
        f.read((char*)&sprite10, sizeof(PrototypeClass10));
        return SpritePrototype(sprite10);

    }   
    throw std::runtime_error("This is not a PK2 legacy sprite!");
}

}