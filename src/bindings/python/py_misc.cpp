#include "py_misc.hpp"
#include "utils/types.hpp"
#include <string>
#include <sstream>


namespace libgreta{

std::string PointToString(Point2D* point){
    std::ostringstream os;
    os<<"("<<point->x<<", "<<point->y<<")";
    return os.str();
}

void ExposeUtils(pybind11::module_& m){

    pybind11::class_<Point2D>(m, "Point2D")
    .def(pybind11::init<double, double>())
    .def_readwrite("x", &Point2D::x)
    .def_readwrite("y", &Point2D::y)
    .def("__str__", PointToString);
}

}