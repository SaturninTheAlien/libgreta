#include "py_zip.hpp"
#include "utils/zip_utils.hpp"


namespace libgreta{

void ExposeZipApi(pybind11::module_& m){
    pybind11::class_<PZip>(m, "PZip")
    .def(pybind11::init<const std::string&>())
    .def("find_subdirectories", &PZip::findSubdirectories);
}

}