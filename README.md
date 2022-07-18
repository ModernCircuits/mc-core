# Modern Circuits - Core

[![License](https://img.shields.io/badge/License-Boost_1.0-lightblue.svg)](https://www.boost.org/LICENSE_1_0.txt)
[![macOS](https://github.com/ModernCircuits/mc-core/actions/workflows/test_macos.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/test_macos.yml)
[![Windows](https://github.com/ModernCircuits/mc-core/actions/workflows/test_windows.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/test_windows.yml)
[![Linux](https://github.com/ModernCircuits/mc-core/actions/workflows/test_linux.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/test_linux.yml)

[![codecov](https://codecov.io/gh/ModernCircuits/mc-core/branch/main/graph/badge.svg?token=F82MD2JEWC)](https://codecov.io/gh/ModernCircuits/mc-core)
[![Coverage](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_coverage.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_coverage.yml)
[![Pre-Commit Hooks](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_pre-commit_hooks.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_pre-commit_hooks.yml)
[![Clang-Tidy](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_clang-tidy.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_clang-tidy.yml)
[![ASAN](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_asan.yml/badge.svg)](https://github.com/ModernCircuits/mc-core/actions/workflows/analyze_asan.yml)

Wrapper around the STL, Boost & other useful libraries. Used internally at [Modern Circuits](https://modern-circuits.com).

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
