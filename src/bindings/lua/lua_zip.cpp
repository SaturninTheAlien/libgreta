#include "lua_zip.hpp"
#include "utils/zip_utils.hpp"


namespace libgreta{

void ExposeZipApi(sol::table& t){
    t.new_usertype<PZip>("PZip",
    sol::constructors<PZip(const std::string&)>(),
    "findSubdirectories", &PZip::findSubdirectories);
}

}
