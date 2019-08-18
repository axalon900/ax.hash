cmake_minimum_required(VERSION 3.14)
project(ax.hashlib)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

add_library(ax.hash INTERFACE)
target_include_directories(ax.hash INTERFACE include)
target_compile_features(ax.hash INTERFACE cxx_std_14)

option(AX_HASH_TESTS "Enables Catch tests" ON)

if (AX_HASH_TESTS)
    find_package(Catch2 REQUIRED)
    set(CMAKE_MODULE_PATH ${Catch2_LIB_DIRS}/cmake/Catch2/ ${CMAKE_MODULE_PATH})
    add_executable(ax.hash-tests test/hash_test.cpp test/main.cpp)
    target_link_libraries(ax.hash-tests PUBLIC ax.hash Catch2::Catch2)

    include(CTest)
    include(Catch)
    catch_discover_tests(ax.hash-tests)
endif()