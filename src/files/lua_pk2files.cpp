#include "lua_pk2files.hpp"
#include "pk2files.hpp"
#include <optional>

namespace libgreta{

void ExposePK2FilesApi(sol::table& t){
    t["SetAssetsPath"] = SetAssetsPath;
    t["GetAssetsPath"] = GetAssetsPath;

    t["SetEpisode"] = SetEpisode;
    t["FindPK2Asset"] = FindPK2Asset_op;
}

}