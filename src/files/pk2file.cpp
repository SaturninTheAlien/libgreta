#include "pk2file.hpp"
#include "utils/string_utils.hpp"
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace fs = std::filesystem;

namespace libgreta{


static void panicWhenFileNotFound(const std::string& path){
	std::ostringstream os;
	os<<"Cannot open the file: \""<<path<<"\"!";
	throw std::runtime_error(os.str());
}

bool File::operator==(const File& second)const {
	if(this->zip_file!=nullptr || second.zip_file!=nullptr){
		return this->zip_file == second.zip_file && this->zip_entry == second.zip_entry;
	}
	else{
		return this->path == second.path;
	}
}

std::string File::getFilename()const{
	return fs::path(this->path).filename().string();
}

std::string File::getExtension()const{
	return PString::lowercase(fs::path(this->path).extension().string());
}

nlohmann::json File::getContentAsJSON()const{
    if(this->zip_file!=nullptr && this->zip_entry.good()){

		char * buffer = new char[this->zip_entry.size + 1];
		buffer[this->zip_entry.size] = '\0';

		this->zip_file->read(this->zip_entry, buffer);

		nlohmann::json res = nlohmann::json::parse(buffer);
		delete[] buffer;
		return res;

	}else{
		std::ifstream in(this->path.c_str());

		if(!in.good()){
			panicWhenFileNotFound(this->path);
		}

		nlohmann::json res = nlohmann::json::parse(in);
		return res;
	}
}


std::string File::getContentAsString()const{
    if(this->zip_file!=nullptr){
		char * buffer = new char[this->zip_entry.size + 1];
		buffer[this->zip_entry.size] = '\0';

		this->zip_file->read(this->zip_entry, buffer);

		std::string res = buffer;
		delete[] buffer;
		return res;
	}
	else{
		std::ifstream in(this->path.c_str());

		if(!in.good()){
			panicWhenFileNotFound(this->path);
		}

		return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	}
}

std::vector<char> File::getContent()const{
    std::vector<char> result;
    if(this->zip_file!=nullptr){
        std::size_t size = this->zip_entry.size;
        result.resize(size);
        this->zip_file->read(this->zip_entry, result.data());
    }
    else{
        std::ifstream in(this->path.c_str(), std::ios::binary|std::ios::ate);

		if(!in.good()){
			panicWhenFileNotFound(this->path);
		}

        std::size_t size = in.tellg();
        in.seekg(0, std::ios::beg);

        result.resize(size);
        in.read(result.data(), size);
        in.close();
    }

    return result;
}

}