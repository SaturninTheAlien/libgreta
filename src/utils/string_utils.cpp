//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
/**
 * @brief
 * String utils by SaturninTheAlien
 */
#include "string_utils.hpp"
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <sstream>

namespace libgreta{

namespace PString{

std::string lowercase(const std::string& src){

    std::string str = src;

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return str;
}

std::string rtrim(const std::string & src){
    std::size_t i = src.size();
    while(i>0){
        --i;
        if(!std::isspace(src[i]))break;
    }

    ++i;
    return src.substr(0, i);
}

std::string unwindowsPath(const std::string& path){
    std::string res = path;
    std::size_t n = path.size();
    for(std::size_t i=0;i<n;++i){
        if(res[i]=='\\'){
            res[i]='/';
        }
    }
    return res;
}


bool endsWith(const std::string& str, const std::string& suffix){
    std::size_t n = suffix.size();
    if(str.size() < n) return false;
    return str.substr(str.size() - n, n)==suffix;
}


std::string removeSuffix(const std::string& str, const std::string& suffix){
    if(endsWith(str, suffix)){
        return str.substr(0, str.size() - suffix.size());
    }
    else{
        return str;
    }
}

}

}