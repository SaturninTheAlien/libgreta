#include "3rd_party/sol.hpp"
#include "utils/api.hpp"

#include "sprite/lua_sprite.hpp"
#include "level/lua_level.hpp"

#include <iostream>

namespace libgreta{


void Test(){
	std::cout<<"Hello world from c++!"<<std::endl;
}


sol::table open_libgreta(sol::this_state L) {
	sol::state_view lua(L);
	sol::table module = lua.create_table();

	module["Test"] = Test;

	ExposeSpritePrototype(module);
	ExposeSpritesIO(module);

	ExposeLevelClasses(module);	
	ExposeLevelIO(module);

	return module;
}


}

extern "C" int GRETA_API luaopen_greta(lua_State* L) {
    return sol::stack::call_lua(
	     L, 1, libgreta::open_libgreta);
}