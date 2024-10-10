#pragma once

#include <string>

namespace Multipass
{
/**
* @brief Helper to compare version strings
* @param one The first version string
* @param two The second version string
* @return bool true if one is less than two
*
*/
bool IsVersionLess(std::string &one, std::string &two);
}
