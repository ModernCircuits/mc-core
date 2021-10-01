if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME conancenter URL https://center.conan.io)
conan_cmake_configure(
    REQUIRES
        boost/1.77.0
        catch2/2.13.7
        concurrentqueue/1.0.3
        fmt/8.0.1
        ms-gsl/3.1.0
        readerwriterqueue/1.0.5
        tcb-span/cci.20200603
    GENERATORS
        cmake_find_package
    OPTIONS
        boost:header_only=True
        catch2:with_main=True
)

conan_cmake_autodetect(settings)

conan_cmake_install(
    PATH_OR_REFERENCE
        .
    BUILD
        outdated
    REMOTE
        conancenter
    SETTINGS
        ${settings}
    SETTINGS
        compiler.cppstd=14
)

