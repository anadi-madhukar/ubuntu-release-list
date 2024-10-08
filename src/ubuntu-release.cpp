#include <iostream>
#include "CurlHTTPRequest.h"

using namespace Multipass;

const std::string kUbuntuReleasesURL = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";;

int main()
{
    CurlHTTPRequest req;
    std::string sRes = req.get(kUbuntuReleasesURL);
    rapidjson::Document doc;
    doc.Parse(sRes.c_str());
    if(doc.HasParseError())
    {
        std::cerr << "Error parsing JSON" << std::endl;
        return 1;
    }
    const rapidjson::Value &releases = doc["products"]["com.ubuntu.cloud:released:download"]["versions"];
    return 0;
}