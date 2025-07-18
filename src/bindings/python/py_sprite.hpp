#pragma once
#include <pybind11/pybind11.h>

namespace libgreta{
void ExposeSpritePrototype(pybind11::module_ & m);
void ExposeSpritesIO(pybind11::module_ &m);

}