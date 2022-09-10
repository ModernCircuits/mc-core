# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.15)
project(test_package LANGUAGES CXX)

find_package(mc-core CONFIG REQUIRED)

add_executable(test_package test_package.cpp)
target_link_libraries(test_package PRIVATE mc::core)
