#include "UbuntuReleaseParser.h"
#include "Utils.h"
#include <iostream>



namespace Multipass
{
  UbuntuReleaseParser::UbuntuReleaseParser(std::string& sJsonContent)
  {
    parse(sJsonContent);
  }

  void UbuntuReleaseParser::printSingleReleaseItem(const std::string& name, UbuntuRelease& ubRelease) {
    std::cout<<"\n-----------------------------"
      <<"\n Release Key:       " << name
      <<"\n Aliases:           " << ubRelease.aliases
      <<"\n Release Name:      " << ubRelease.releaseName
      <<"\n Release Code Name: " << ubRelease.releaseCodeName
      <<"\n Release Title:     " << ubRelease.releaseTitle
      <<"\n-----------------------------";
  }

  void UbuntuReleaseParser::printSingleVersionItem(const std::string& name, Version& ubVersion)
  {
    std::cout << "\n\t"
      <<"Version:  " << name
      <<"\n\t  pubName:  " << ubVersion.pubName
      <<"\n\t  sha256:   " << ubVersion.diskImgSha;
  }

  void UbuntuReleaseParser::printUbuntuReleases()
  {

    for (auto& release : ubuntuReleases_) {
      printSingleReleaseItem(release.first, release.second);

      for (auto& version : release.second.versions) {
        printSingleVersionItem(version.first, version.second);
      }

    }
  }

  void UbuntuReleaseParser::printLatestLTSRelease()
  {
    printf("\nCurrent LTS Release: \n");
    printSingleReleaseItem(currLtsRelease_.first, currLtsRelease_.second);
  }

  void UbuntuReleaseParser::printSha256ofRelease(const std::string& releaseName,
    const std::string& version)
  {
    auto it = ubuntuReleases_.find(releaseName);
    if (it == ubuntuReleases_.end()) {
      std::cout << "\nError: Release not found!\n";
      return;
    }
    auto& release = it->second;
    auto it2 = release.versions.find(version);
    if (it2 == release.versions.end()) {
      std::cout << "\nError: Version not found!\n";
      return;
    }
    printSingleReleaseItem(releaseName, release);
    printSingleVersionItem(version, it2->second);
  }

  bool UbuntuReleaseParser::parse(std::string& sJsonContent)
  {
    rapidjson::Document doc;
    doc.Parse(sJsonContent.c_str());
    try
    {
      if (!doc.HasMember("products")) {
        std::cout << "\nError : Invalid Json format!\n";
        return false;
      }
      auto& products = doc["products"];
      if (!products.IsObject()) {
        std::cout << "\nError : Invalid Json format at products level!\n";
        return false;
      }

      for (auto& product : products.GetObject()) {
        if (!product.value.IsObject()) {
          std::cout << "\nError : Invalid Json format at product level!\n";
          continue;
        }
        UbuntuRelease release;
        auto productObj = product.value.GetObject();
        if ((!productObj.HasMember("arch")) ||
          (!productObj["arch"].IsString())) {
          continue;
        }
        if (strcmp(productObj["arch"].GetString(), "amd64") != 0) {
          continue;
        }
        if ((!productObj.HasMember("supported")) ||
          (!productObj["supported"].IsBool())) {
          continue;
        }
        if (productObj["supported"].GetBool() == false) {
          continue;
        }

        // We are here only if arch:amd64 and supported:true
        std::string sReleaseKey = product.name.GetString();

        if ((productObj.HasMember("aliases")) && (productObj["aliases"].IsString())) {
          release.aliases = productObj["aliases"].GetString();
        }
        if ((productObj.HasMember("release")) && (productObj["release"].IsString())) {
          release.releaseName = productObj["release"].GetString();
        }
        if ((productObj.HasMember("release_codename")) && (productObj["release_codename"].IsString())) {
          release.releaseCodeName = productObj["release_codename"].GetString();
        }
        if ((productObj.HasMember("release_title")) && (productObj["release_title"].IsString())) {
          release.releaseTitle = productObj["release_title"].GetString();
        }
        if ((productObj.HasMember("version")) && (productObj["version"].IsString())) {
          release.versionNum = productObj["version"].GetString();
        }
        if (currLtsRelease_.first.empty() ||
          IsVersionLess(currLtsRelease_.second.versionNum, release.versionNum)) {
          currLtsRelease_ = { sReleaseKey, release };
        }

        if (productObj.HasMember("versions") && productObj["versions"].IsObject())
        {
          auto& versions = productObj["versions"];
          for (auto& prodVersion : versions.GetObject()) {
            std::string sVersion = prodVersion.name.GetString();
            auto& prodVersionObj = prodVersion.value;
            Version version{ "","" };
            if (prodVersionObj.HasMember("items") &&
              prodVersionObj["items"].IsObject()) {
              auto prodItems = prodVersionObj["items"].GetObject();
              if (prodItems.HasMember("disk1.img") &&
                prodItems["disk1.img"].IsObject() &&
                prodItems["disk1.img"].HasMember("sha256") &&
                prodItems["disk1.img"]["sha256"].IsString()) {
                version.diskImgSha = prodItems["disk1.img"]["sha256"].GetString();
              }
            }
            if (prodVersionObj.HasMember("pubname") &&
              prodVersionObj["pubname"].IsString()) {
              version.pubName = prodVersionObj["pubname"].GetString();
            }
            if (!version.diskImgSha.empty() || !version.pubName.empty()) {
              release.versions[sVersion] = version;
            }
          }
        }
        ubuntuReleases_[sReleaseKey] = release;
      }
      return !ubuntuReleases_.empty();
    }
    catch (std::exception& e) {
      std::cout << "\nError: Exception Parsing json: %s\n", e.what();
    }
    return false;
  }
}
