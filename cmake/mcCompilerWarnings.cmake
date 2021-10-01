add_library(mc_compiler_warnings INTERFACE)
add_library(mc::compiler_warnings ALIAS mc_compiler_warnings)

if (MSVC)
    if (MC_BUILD_WERROR)
        target_compile_options(mc_compiler_warnings INTERFACE /WX)
    endif (MC_BUILD_WERROR)
    target_compile_options(mc_compiler_warnings INTERFACE /W3)
else ()
    if (MC_BUILD_WERROR)
        target_compile_options(mc_compiler_warnings INTERFACE -Werror)
    endif (MC_BUILD_WERROR)
    target_compile_options(mc_compiler_warnings
            INTERFACE
                    -Wall
                    -Wextra
                    -Wpedantic
                    -Wcast-align
                    -Wshadow
                    -Wunused-parameter
                    -Wnarrowing
                    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
                        #-Weverything
                    >
                    $<$<CXX_COMPILER_ID:AppleClang>:
                        -Wno-poison-system-directories
                    >
                    $<$<CXX_COMPILER_ID:GNU>:
                        #-Wlogical-op
                    >
            )

endif (MSVC)
