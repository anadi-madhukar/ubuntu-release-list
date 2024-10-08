# ubuntu-release-list

A command-line based http client to query latest Ubuntu versions and releases. 

## Usage: 

Just launch the compiled executable on any machine.

After launching, the program will parse the ubuntu releases json present at `https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json`

It will populate an internal map of data structures listing down various releases and their versions. 

All non supported versions are ignored. All versions for machine architectures different than amd64 are ignored. 

User will then get a menu to choose one of the following options :
1. List currently supported amd64 releases
2. List current LTS version. 
3. List the disk.img sha256 of a release and version combo. This requires user to input a valid release key and version.
4. Quit the program

The menu runs in a loop and does not quit after first run. 
The Json is loaded and parsed only once per run of the program


## Building
This code compiles on all 3 OS: Win32, MacOsX and Linux 

Dependencies are :
1. `cmake` version 3.12 or above 
2. `build-essential` on Linux  / Visual Studio on Windows / XCode on MacOSX

Submodules:
1. openssl-cmake: This compiles openssl based on native compiler on Linux, uses systemp openssl on MacOSX and is Ignored on Windows
2. libCurl: This is used to make Https request
3. rapidjsn: This is used to parse the json response

Building steps: 
```
git clone --recursive https://github.com/anadi-madhukar/ubuntu-release-list.git
mkdir build; cd build
cmake ..
cmake --build .
```

## Testing 
ON Linux and Mac just launch `./src/ubuntu-release-list` while in build directory

On Windows, launch `.\src\Debug\ubuntu-release-list.exe`

