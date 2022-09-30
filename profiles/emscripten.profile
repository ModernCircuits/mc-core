[settings]
os=Emscripten
arch=wasm

compiler=clang
compiler.version=16
compiler.libcxx=libc++

[options]

[tool_requires]
emsdk/3.1.23

[env]

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
