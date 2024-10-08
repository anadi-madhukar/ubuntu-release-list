cmake_minimum_required(VERSION 3.12...3.27)
project(ubuntu-release-list)

if(WIN32)
    # For WIN32, we use the prebuilt Schannel binaries, Openssl Not needed
    set(CURL_ENABLE_SSL ON)
    set(CURL_USE_SCHANNEL ON)
else()
    # For Linux and MacOS, we build Openssl and use it with Curl
    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -pthread)
    SET(OPENSSL_CMAKE_FLAGS -DOPENSSL_USE_STATIC_LIBS=TRUE -DCMAKE_CXX_FLAGS=-pthread)

    if(APPLE)
        # For MacOS, we use the system Openssl
        set(OPENSSL_CMAKE_FLAGS ${OPENSSL_CMAKE_FLAGS} -DSYSTEM_OPENSSL=ON)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -std=c++11")
    else()
        # For Linux, we build Openssl
        set(OPENSSL_CMAKE_FLAGS ${OPENSSL_CMAKE_FLAGS} -DBUILD_OPENSSL=ON -DOPENSSL_BUILD_VERSION=3.3.2 .)
    endif()

    # Build Openssl
    set(CMAKE_CMD_WITH_ARGS ${CMAKE_COMMAND} ${OPENSSL_CMAKE_FLAGS})
    execute_process(
        COMMAND ${CMAKE_CMD_WITH_ARGS}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/third-party/openssl-cmake"
        COMMAND_ECHO  STDOUT)

    execute_process(
        COMMAND make
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/third-party/openssl-cmake")
    set(OPENSSL_ROOT_DIR "${PROJECT_SOURCE_DIR}/third-party/openssl-cmake/openssl-build/usr/local")
endif()

# Set bunch of flags t disable unwanted features in libcurl
set(CURL_DISABLE_NTLM ON)
set(BUILD_CURL_EXE OFF)
set(BUILD_TESTING OFF)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
set(BUILD_STATIC_CURL ON)
set(CURL_DISABLE_INSTALL ON)
set(CURL_DISABLE_COOKIES ON)
set(CURL_DISABLE_BASIC_AUTH ON)
set(CURL_DISABLE_BEARER_AUTH ON)
set(CURL_DISABLE_DIGEST_AUTH ON)
set(CURL_DISABLE_KERBEROS_AUTH ON)
set(CURL_DISABLE_NEGOTIATE_AUTH ON)
set(CURL_DISABLE_AWS ON)
set(CURL_DISABLE_DICT ON)
set(CURL_DISABLE_DOH ON)
set(CURL_DISABLE_FILE ON)
set(CURL_DISABLE_FTP ON)
set(CURL_DISABLE_IMAP ON)
set(CURL_DISABLE_LDAP ON)
set(CURL_DISABLE_LDAPS ON)
set(CURL_DISABLE_POP3 ON)
set(CURL_DISABLE_SMB ON)
set(CURL_DISABLE_SMTP ON)
set(CURL_DISABLE_TELNET ON)
set(CURL_DISABLE_TFTP ON)
add_subdirectory(third-party/curl)

# Add the subdirectory src
add_subdirectory(src)
