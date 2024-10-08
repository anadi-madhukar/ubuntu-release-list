#include <string>
#include "rapidjson/document.h"

namespace Multipass{
struct UbuntuRelease
{
    std::string alises;
    std::string releaseName;
    std::string releaseCodeName;
    std::string releaseTitle;
};
}