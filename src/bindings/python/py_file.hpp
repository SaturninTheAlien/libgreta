#pragma once
#include <pybind11/pybind11.h>

namespace libgreta{
void ExposeFileClass(pybind11::module_ & m);
//void ExposeFilesystemAPI(pybind11::module_ & m);

}