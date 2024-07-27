#pragma once

#include <vector>
#include "utils/types.hpp"
#include "utils/api.hpp"

namespace libgreta{

class GRETA_API TilesArray{
public:
    TilesArray(std::size_t size);
    TilesArray(const TilesArray& src);
    TilesArray(TilesArray&&src);

    ~TilesArray();

    TilesArray & operator= (TilesArray& src)=delete;
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
};

}
