#include "3rd_party/sol.hpp"
#include "utils/api.hpp"
#include "sprite/lua_sprite.hpp"

namespace libgreta{

    sol::table open_libgreta(sol::this_state L) {
		sol::state_view lua(L);
		sol::table module = lua.create_table();

        ExposeSpritePrototype(module);

		return module;
	}
}

extern "C" int GRETA_API luaopen_greta(lua_State* L) {
    return sol::stack::call_lua(
	     L, 1, libgreta::open_libgreta);
}