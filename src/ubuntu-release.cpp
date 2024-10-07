#include <iostream>
#include "CurlHTTPRequest.h"

using namespace Multipass;

int main()
{
    CurlHTTPRequest req;
    std::string sRes = req.get("https://www.google.com");
    printf("\n%s\n", sRes.c_str());
    return 0;
}