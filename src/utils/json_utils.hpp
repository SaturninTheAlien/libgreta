#pragma once
#include "3rd_party/json.hpp"
#include <vector>
#include <string>
#include <ostream>
#include <istream>
#include "types.hpp"

namespace libgreta{

void jsonReadString(const nlohmann::json& j, const std::string& name, std::string& target);
void jsonReadInt(const nlohmann::json& j, const std::string& name, int& target);
void jsonReadDouble(const nlohmann::json& j, const std::string& name, double& target );
void jsonReadBool(const nlohmann::json& j, const std::string& name, bool& target);
void jsonReadU32(const nlohmann::json& j, const std::string& name, u32& target);

void jsonReadEnumU8(const nlohmann::json& j, const std::string& name, u8& target);

void jsonReadEnumU8(const nlohmann::json& j, const std::string& name, u8& target,
    const std::map<std::string, u8>& namedValues);

nlohmann::json ReadCBOR(std::istream& in);
void WriteCBOR(std::ostream& out, const nlohmann::json& j);

}