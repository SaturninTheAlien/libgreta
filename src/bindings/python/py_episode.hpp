#pragma once
#include <pybind11/pybind11.h>

namespace libgreta{

void ExposeEpisode(pybind11::module_ & m);

}