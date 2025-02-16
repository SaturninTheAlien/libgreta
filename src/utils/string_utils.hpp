#pragma once
#include <string>
#include "types.hpp"
#include "api.hpp"

namespace libgreta{

/**
 * @brief 
 * Convert a string to lowercase
 */
GRETA_API std::string lowercase(const std::string& src);
/**
 * @brief 
 * Remove white characters at the end of a string
 */
GRETA_API std::string rtrim(const std::string & src);

/**
 * @brief 
 * Replace '\\' with '/'
 */
GRETA_API std::string unwindowsPath(const std::string& path);


GRETA_API bool endsWith(const std::string& str, const std::string& suffix);
GRETA_API std::string removeSuffix(const std::string& str, const std::string& suffix);

}