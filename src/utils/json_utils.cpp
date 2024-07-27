#include "json_utils.hpp"
#include <sstream>

namespace libgreta{

void jsonReadString(const nlohmann::json& j, const std::string& name, std::string& target){
	if(j.contains(name)){
		target = j[name].get<std::string>();
	}
}

void jsonReadInt(const nlohmann::json& j, const std::string& name, int& target){
	if(j.contains(name)){
		target = j[name].get<int>();
	}
}

void jsonReadDouble(const nlohmann::json& j, const std::string& name, double& target ){
	if(j.contains(name)){
		target = j[name].get<double>();
	}
}

void jsonReadBool(const nlohmann::json& j, const std::string& name, bool& target){
	if(j.contains(name)){
		target = j[name].get<bool>();
	}
}

void jsonReadU32(const nlohmann::json& j, const std::string& name, u32& target){
	if(j.contains(name)){
		target = j[name].get<u32>();
	}
}

void jsonReadEnumU8(const nlohmann::json& j, const std::string& name, u8& target){
	if(j.contains(name)){
		int res = j[name].get<int>();
		target= (u8) res;
	}
}

void jsonReadEnumU8(const nlohmann::json& j, const std::string& name, u8& target,
	const std::map<std::string, u8>& namedValues){
	
	if(j.contains(name)){
		const nlohmann::json& field = j[name];
		if(field.is_number_integer()){
			int res = field.get<int>();
			target = (u8) res;
		}
		else if(field.is_string()){
			std::string field_str = field.get<std::string>();
			auto it = namedValues.find(field_str);
			if(it!=namedValues.end()){
				target = it->second;
			}
			else{
				std::ostringstream os;
				os<<"Unknown named enum value: \""
				<<field_str<<"\" of field \""<<name<<"\"";
				std::string s=os.str();
				throw std::runtime_error(s.c_str());
			}
		}
	}
}

void WriteCBOR(std::ostream& out, const nlohmann::json& j){
	std::vector<std::uint8_t> v_cbor = nlohmann::json::to_cbor(j);
	u64 size = v_cbor.size();
	out.write((char*)&size, sizeof(u64));
	out.write((char*)v_cbor.data(), size);
}

nlohmann::json ReadCBOR(std::istream& in){
	u64 size=0;
	in.read((char*)&size, sizeof(u64));

	std::vector<std::uint8_t> v_cbor;
	v_cbor.resize(size);

	in.read((char*)v_cbor.data(), size);

	return nlohmann::json::from_cbor(v_cbor);
}


}