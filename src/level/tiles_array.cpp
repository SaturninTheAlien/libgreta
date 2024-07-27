#include "tiles_array.hpp"

namespace libgreta{

TilesArray::TilesArray(std::size_t size):
mSize(size){

    if(this->mSize > 0){
        this->mTiles = new u8[this->mSize];
        memset(this->mTiles, u8(255), this->mSize);
    }
}

TilesArray::TilesArray(const TilesArray&src):
mSize(src.mSize){
    if(this->mSize > 0){
        this->mTiles = new u8[this->mSize];
        memcpy(this->mTiles, src.mTiles, this->mSize);
    }
}


TilesArray::TilesArray(TilesArray&&src):
 mTiles(src.mTiles), mSize(src.mSize){
    src.mTiles = nullptr; 
}

TilesArray::~TilesArray(){
    if(this->mTiles!=nullptr){
        delete [] this->mTiles;
        this->mTiles = nullptr;
    }
}


}