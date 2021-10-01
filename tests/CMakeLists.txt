project(mc_stl_tests)

enable_testing()
include(CTest)
find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        Catch2::Catch2WithMain 
        mc::compiler_options
        mc::compiler_warnings
        mc::coverage
)

target_sources(${PROJECT_NAME}
    PRIVATE
        any.cpp
)