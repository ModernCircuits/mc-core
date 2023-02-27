Development
===========

Setup
-----

.. code-block:: shell

    sudo apt install cmake ninja
    pip install conan
    conan profile detect --force
    conan profile update conf.tools.cmake.cmaketoolchain:generator=Ninja default

Compile
-------

.. code-block:: shell

    conan install -if build --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=20 -s build_type=Debug .
    conan install -if build --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=20 -s build_type=Release .

    cmake -S . -Bbuild -G "Ninja Multi-Config" -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" -DCMAKE_CXX_STANDARD=20

    cmake --build build --config Debug
    cmake --build build --config Release

    ctest --test-dir build -C Debug
    ctest --test-dir build -C Release
