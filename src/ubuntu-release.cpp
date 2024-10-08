#include <iostream>
#include "CurlHTTPRequest.h"
#include "UbuntuReleaseParser.h"

using namespace Multipass;

const std::string kUbuntuReleasesURL = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
;

void keyBoardInteract(std::string &sResponse)
{
  UbuntuReleaseParser parser(sResponse);
  bool quit = false;
  std::cout << "\n\n This programs parses and lists currently supported Ubuntu releases "
               "as mentioned at: cloud-images.ubuntu.com\n\n";

  while (!quit)
  {
    std::cout << "\n\n";
    std::cout << "\n***************CHOOSE AN OPTION*******************\n";
    std::cout << "1. List down currently supported Ubuntu releases\n";
    std::cout << "2. List Current (Highest) LTS release\n";
    std::cout << "3. List sha256 of an Ubuntu release (interactive)\n";
    std::cout << "4. (Or any other key) : Quit\n";
    std::cout << "\n*************************************************\n";

    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
      parser.printUbuntuReleases();
      break;
    case 2:
      parser.printLatestLTSRelease();
      break;
    case 3:
    {
      std::string releaseName, releaseVersion;
      std::cout << "\nEnter the release name:\n";
      std::cin >> releaseName;
      std::cout << "\nEnter release version:\n";
      std::cin >> releaseVersion;
      parser.printSha256ofRelease(releaseName, releaseVersion);
    }
    break;
    case 4:
      return;
    }
  }
}

int main()
{
  CurlHTTPRequest req;
  std::string sRes = req.get(kUbuntuReleasesURL);
  if (sRes.empty())
  {
    std::cout << "Failed to get Ubuntu releases data" << std::endl;
    return 1;
  }
  keyBoardInteract(sRes);
  return 0;
}