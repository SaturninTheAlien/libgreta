#include "3rd_party/sol.hpp"
#include "utils/api.hpp"

#include "lua_misc.hpp"
#include "lua_sprite.hpp"
#include "lua_level.hpp"
#include "lua_files.hpp"
#include "lua_episode.hpp"
#include "lua_zip.hpp"

#include <iostream>

namespace libgreta{

void Test(){
	std::cout<<"Hello world from c++!"<<std::endl;
}


sol::table open_libgreta(sol::this_state L) {
	sol::state_view lua(L);
	sol::table module = lua.create_table();

	module["Test"] = Test;

	ExposeUtils(module);
	ExposeSpritePrototype(module);
	ExposeSpritesIO(module);
	ExposeLevelClasses(module);	
	ExposeLevelIO(module);

	ExposeZipApi(module);
	
	ExposeEpisode(module);

	ExposeFileClass(module);

	sol::table lua_fs = lua.create_table();
	module["fs"] = lua_fs;
	ExposeFilesystemAPI(lua_fs);

	return module;
}

}

extern "C" int GRETA_API luaopen_greta_lua(lua_State* L) {
    return sol::stack::call_lua(
	     L, 1, libgreta::open_libgreta);
}