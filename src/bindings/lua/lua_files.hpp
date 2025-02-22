#pragma once
#include "3rd_party/sol.hpp"

namespace libgreta{

void ExposeFileClass(sol::table& t);
void ExposeFilesystemAPI(sol::table& t);

}