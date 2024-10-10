#pragma once
#include "HTTPRequestInterface.h"
#include <curl/curl.h>

namespace Multipass
{
/**
 *
 * @brief A class that implements the HTTPRequestInterface using libcurl
 *
 **/
class CurlHTTPRequest : public HTTPRequestInterface
{
public:
    CurlHTTPRequest();
    ~CurlHTTPRequest();
    /**
     * @brief HTTP GET request method using libCURL.
     * @param url The url to request data from
     * @return std::string The data returned from the server
     *
     */
    std::string get(const std::string &url) override;
    /**
     * @brief HTTP POST  request method using libCURL.
     * @param url The url to request data from
     * @param data The data to post to the server
     * @return std::string The data returned from the server
     *
     */
    std::string post(const std::string &url, const std::string &data) override
    {
        // Not implemented
        return "";
    };

private:
    // The curl library handle to send requests
    CURL *curlHandle_;

private:
    // Helper Function to set the callback data object
    void setCurlCallbackData(std::string *sData);
    // Static method curl calls when request completes (or fails)
    static size_t setResponseCb(char *responseChunk, size_t count,
                                size_t bytesPerCount, void *userdata);
};
}