#pragma once

#include <string>
#include <map>
#include "rapidjson/document.h"

namespace Multipass
{

// Structure to hold the version information
// of a particular Ubuntu release-version combo
struct Version
{
  std::string pubName;
  std::string diskImgSha;
};

// Structure to hold the Ubuntu release information
struct UbuntuRelease
{
  std::string aliases;
  std::string releaseName;
  std::string releaseCodeName;
  std::string releaseTitle;
  std::string versionNum;
  std::map<std::string, Version> versions;
};


/**
 * @brief Class to parse and print Ubuntu releases and versions
 *
*/
class UbuntuReleaseParser
{
public:
  /**
   * @brief Construtor that takes the json content and parses it
   *
  */
  UbuntuReleaseParser(std::string &sJsonContent);
  ~UbuntuReleaseParser() {}

  /**
  * @brief Method to print all Ubuntu releases and their versions
  * @param None
  * @return None
  */
  void printUbuntuReleases();

  /**
  * @brief Method to print latest LTS Ubuntu release
  * @param None
  * @return None
  */
  void printLatestLTSRelease();

  /**
  * @brief Method to print sha256 of disk.img of a particular release
  * @param releaseName : Name of Ubuntu release 
  * @param version : Version of the Specific Ubuntu release
  * @return None
  */
  void printSha256ofRelease(const std::string &releaseName, const std::string &version);

private:
  // Internal method to parse the json content
  bool parse(std::string &sJsonContent);
  // Internal method to print a single release item
  void printSingleReleaseItem(const std::string &name,
                              UbuntuRelease &ubRelease);
  // Internal method to print a single version item
  void printSingleVersionItem(const std::string &name,
                              Version &ubVersion);

private:
  std::map<std::string, UbuntuRelease> ubuntuReleases_;
  std::pair<std::string, UbuntuRelease> currLtsRelease_{{""}, {}};
};
}