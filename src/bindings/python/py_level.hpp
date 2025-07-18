#pragma once
#include <pybind11/pybind11.h>

namespace libgreta{

void ExposeLevel(pybind11::module_ & m);
void ExposeLevelIO(pybind11::module_ & m);


}