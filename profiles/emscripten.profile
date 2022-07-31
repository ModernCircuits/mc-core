[settings]
os=Emscripten
arch=wasm

compiler=clang
compiler.version=15
compiler.libcxx=libc++

[options]

[tool_requires]
emsdk/3.1.16

[env]

[conf]
tools.cmake.cmaketoolchain:generator=Ninja
