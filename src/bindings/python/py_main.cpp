#include <pybind11/pybind11.h>

#include "py_misc.hpp"
#include "py_sprite.hpp"
#include "py_level.hpp"
#include "py_zip.hpp"
#include "py_file.hpp"
#include "py_episode.hpp"

PYBIND11_MODULE(py_greta, m) {
    m.doc() = "LibGreta - Pekka Kana 2 utils lib";

    libgreta::ExposeSpritePrototype(m);
    libgreta::ExposeSpritesIO(m);
    libgreta::ExposeUtils(m);
    libgreta::ExposeLevel(m);
    libgreta::ExposeLevelIO(m);
    libgreta::ExposeZipApi(m);
    libgreta::ExposeFileClass(m);
    libgreta::ExposeEpisode(m); 
}
