add_executable(ubuntu-release-list "ubuntu-release.cpp")
target_link_libraries (ubuntu-release-list
                       libcurl
                       )