
#include "CurlHTTPRequest.h"

namespace Multipass
{

CurlHTTPRequest::CurlHTTPRequest()
{
    curlHandle_ = curl_easy_init();
}
CurlHTTPRequest::~CurlHTTPRequest()
{
    if (curlHandle_)
    {
        curl_easy_cleanup(curlHandle_);
    }
}
std::string CurlHTTPRequest::get(const std::string &url)
{
    CURLcode resposeCode;
    char buf[32];
    long httpResponseCode = 0;
    std::string sResponse("");

    if (!curlHandle_)
    {
        printf("\nError: Failed in initializing Curl. Aborting\n");
        return sResponse;
    }

    printf("\nInfo: Sending GET request to %s\n", url.c_str());
    curl_easy_setopt(curlHandle_, CURLOPT_URL, url.c_str());
    setCurlCallbackData(&sResponse);
    /* Perform the request, res will get the return code */
    resposeCode = curl_easy_perform(curlHandle_);
    printf("\nResponse received ..\n");

    /* Check for errors */
    if (resposeCode != CURLE_OK)
    {
        printf("\ncurl_easy_perform() failed: %s\n",
                curl_easy_strerror(resposeCode));
        goto cleanup;
    }
    curl_easy_getinfo(curlHandle_, CURLINFO_RESPONSE_CODE, &httpResponseCode);
    printf("\nHTTP Response code: %d\n", httpResponseCode);

cleanup:

    if (curlHandle_)
        curl_easy_reset(curlHandle_);

    return sResponse;
}

size_t CurlHTTPRequest::setResponseCb(char *responseChunk, size_t count,
                                      size_t bytesPerCount, void *userdata)
{
    size_t bytesReceived = count * bytesPerCount;
    std::string *responseString = (std::string *)userdata;
    responseString->append(responseChunk, bytesReceived);
    return bytesReceived;
}
void CurlHTTPRequest::setCurlCallbackData(std::string *sData)
{

    curl_easy_setopt(curlHandle_, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curlHandle_, CURLOPT_WRITEFUNCTION, setResponseCb);
    curl_easy_setopt(curlHandle_, CURLOPT_WRITEDATA, sData);
}
}