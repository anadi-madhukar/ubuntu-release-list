#include <string>

namespace Multipass
{
/**
 * @brief HTTP request virtual base class.
 *
 * This is an interface that defines the methods that
 * a HTTPRequest class should implement
 * Implement his class to furnish get and post HTTP
 * requests using an underlying mechanism like cURL or WinHTTP
 *
 */
class HTTPRequestInterface
{
public:
    virtual ~HTTPRequestInterface() {}
    /**
     *
     * @brief Method to request data from a web server using get request
     * @param url The url to request data from
     * @return std::string The data returned from the server
     */
    virtual std::string get(const std::string &url) = 0;
    /**
     * @brief Method to request data from a web server using get request
     * @param url The url to request data from
     * @return std::string The data returned from the server
     */
    virtual std::string post(const std::string &url, const std::string &data) = 0;
};
}