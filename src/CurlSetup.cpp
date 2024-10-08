#include <curl/curl.h>

/**
 *
 * @brief A class whose global static variable is used to
 * initialize and deinitialize curl global state
 *
 **/
class CurlSetup
{
public:
    CurlSetup()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~CurlSetup()
    {
        curl_global_cleanup();
    }
};
CurlSetup g_curlSetup;