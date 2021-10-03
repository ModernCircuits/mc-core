#pragma once

#if __has_include(<version>)
    #include <version>
#endif

#if __cplusplus > 202002L
    #define MC_CPPSTD 23
    #define MC_CPPSTD23
#elif __cplusplus > 201703L
    #define MC_CPPSTD 20
    #define MC_CPPSTD20
#elif __cplusplus > 201402L
    #define MC_CPPSTD 17
    #define MC_CPPSTD17
#elif __cplusplus > 201103L
    #define MC_CPPSTD 14
    #define MC_CPPSTD14
#else
    #error "C++14 is the minimum required standard"
#endif