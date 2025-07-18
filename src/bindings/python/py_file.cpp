#include "py_file.hpp"

#include "utils/file.hpp"
#include <optional>
#include <filesystem>

namespace libgreta{

static std::string Py_FileToStr(File* file){
    if(file->isZip()){
        return std::string("zip:/") + file->str();   
    }
    else{
        return file->str();
    }
}
/*
static bool Py_IsAbsolute(const std::string& s){
    return std::filesystem::path(s).is_absolute();
}

static bool Py_Exists(const std::string& s){
    return std::filesystem::exists(s);
}

static bool Py_IsDir(const std::string& s){
    return std::filesystem::is_directory(s);
}*/


void ExposeFileClass(pybind11::module_ & m){
    pybind11::class_<File>(m, "File")
    .def(pybind11::init<const std::string&>())
    .def("is_zip", &File::isZip)
    .def("get_filename", &File::getFilename)
    .def("get_extension", &File::getExtension)
    .def("get_content", &File::getContent)
    .def("get_content_as_string", &File::getContentAsString)
    .def("__str__", Py_FileToStr);
}

}