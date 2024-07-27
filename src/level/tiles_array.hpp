#pragma once

#include <vector>
#include "utils/types.hpp"
#include "utils/api.hpp"
#include <ostream>
#include <istream>

namespace libgreta{

enum{
    TILES_COMPRESSION_NONE = 0,
    TILES_OFFSET_NEW = 1,
    TILES_OFFSET_LEGACY = 2
};

class GRETA_API TilesArray{
public:
    TilesArray(std::size_t size);
    TilesArray(const TilesArray& src);
    TilesArray(TilesArray&&src);

    ~TilesArray();

    TilesArray & operator= (const TilesArray& src)=delete;
    TilesArray & operator= (TilesArray&& src)=delete;

    u8& operator[](int index){
        return this->mTiles[index];
    }

    const u8& operator[](int index)const{
        return this->mTiles[index];
    }

    u8* begin(){
        return this->mTiles;
    }

    u8* end(){
        return this->mTiles + this->mSize;
    }

    std::size_t size()const{
        return this->mSize;
    }

private:
    u8* mTiles = nullptr;
    std::size_t mSize = 0;
    friend void WriteTilesArray(std::ostream& out, const TilesArray& array, int compression);
    friend void ReadTilesArray(std::istream& in, TilesArray& array,
        u32 level_width,
        u32 level_height,
        int compression);

};

}
