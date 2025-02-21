#include "lua_zip.hpp"
#include "utils/zip_utils.hpp"
#include "files/pk2file.hpp"
#include "files/pk2filesystem.hpp"


namespace libgreta{


std::vector<std::string> findEpisodeNames(PZip* zip){
    return zip->findSubdirectories("episodes");
}


void ExposeZipApi(sol::table& t){
    t.new_usertype<PZip>("PZip",
    sol::constructors<PZip(const std::string&)>(),
    "findSubdirectories", &PZip::findSubdirectories,
    "findEpisodeNames", findEpisodeNames);
}

}
