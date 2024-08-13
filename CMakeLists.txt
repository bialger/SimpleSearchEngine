cmake_minimum_required(VERSION 3.12)

project(
        SimpleSearchEngine
        VERSION 1.0
        DESCRIPTION "Simple Search Engine by bialger"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_BUILD_FLAGS "/Wall")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_BUILD_FLAGS "-Wall")
endif ()

add_subdirectory(lib)
add_subdirectory(bin)


enable_testing()
add_subdirectory(tests)
