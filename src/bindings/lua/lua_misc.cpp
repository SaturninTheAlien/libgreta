#include "lua_misc.hpp"
#include "utils/types.hpp"
#include <string>
#include <sstream>


namespace libgreta{

std::string PointToString(Point2D* point){
    std::ostringstream os;
    os<<"("<<point->x<<", "<<point->y<<")";
    return os.str();
}

void ExposeUtils(sol::table& t){
    t.new_usertype<Point2D>("Point2D",
    "x", &Point2D::x,
    "y", &Point2D::y,
    "__tostring", PointToString);
}

}