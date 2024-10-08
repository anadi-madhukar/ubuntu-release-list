include_directories("${CMAKE_SOURCE_DIR}/third-party/rapidjson/include")

add_executable(ubuntu-release-list 
             "CurlHttpRequest.cpp"
             "CurlSetup.cpp"
             "CurlSetup.cpp"
             "CurlSetup.cpp"
             "UbuntuReleaseParser.cpp"
             "Utils.cpp"
             "ubuntu-release.cpp")

target_link_libraries (ubuntu-release-list
                       libcurl)    