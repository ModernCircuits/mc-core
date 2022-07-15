# Modern Circuits - STL

Wrapper around the STL, Boost & other useful libraries. Used internally at [Modern Circuits](https://modern-circuits.com).

## Status

|                                                                                  macOS                                                                                   |                                                                                    Windows                                                                                     |                                                                                  Linux                                                                                   |
| :----------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
| [![macOS](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_macos.yml/badge.svg)](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_macos.yml) | [![Windows](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_windows.yml/badge.svg)](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_windows.yml) | [![Linux](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_linux.yml/badge.svg)](https://github.com/ModernCircuits/mcSTL/actions/workflows/test_linux.yml) |

## Build

### Setup

```sh
sudo apt install cmake ninja
pip install conan
conan config init
conan profile update conf.tools.cmake.cmaketoolchain:generator=Ninja default
```

### Compile

```sh
conan install -if build --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=20 -s build_type=Debug .
conan install -if build --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=20 -s build_type=Release .

cmake -S . -Bbuild -G "Ninja Multi-Config" -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" -DCMAKE_CXX_STANDARD=20

cmake --build build --config Debug
cmake --build build --config Release

ctest --test-dir build -C Debug
ctest --test-dir build -C Release
```
