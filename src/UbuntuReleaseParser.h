#pragma once

#include <string>
#include <map>
#include "rapidjson/document.h"

namespace Multipass{
  struct Version {
    std::string pubName;
    std::string diskImgSha;
  };
struct UbuntuRelease
{
    std::string aliases;
    std::string releaseName;
    std::string releaseCodeName;
    std::string releaseTitle;
    std::string versionNum;
    std::map<std::string, Version>versions;
};

class UbuntuReleaseParser
{
public:
  UbuntuReleaseParser(std::string& sJsonContent);
  ~UbuntuReleaseParser() {}
  void printUbuntuReleases();
  void printLatestLTSRelease();
  void printSha256ofRelease(const std::string& releaseName, const std::string& version);
private:
  bool parse(std::string& sJsonContent);
  void printSingleReleaseItem(const std::string& name, 
                              UbuntuRelease& ubRelease);
  void printSingleVersionItem(const std::string& name,
                              Version& ubVersion);
private:
  std::map < std::string, UbuntuRelease> ubuntuReleases_;
  std::pair <std::string, UbuntuRelease> currLtsRelease_{ {""},{} };
};
}