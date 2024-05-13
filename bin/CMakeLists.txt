add_executable(${PROJECT_NAME}Indexer indexer.cpp)

add_executable(${PROJECT_NAME} searcher.cpp)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release) # Main executable should be built with Release
endif()

message(STATUS "Main executable build type: ${CMAKE_BUILD_TYPE}")

target_link_libraries(${PROJECT_NAME}Indexer PUBLIC
        index
        argparser
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        index
        search
        argparser
)

target_include_directories(${PROJECT_NAME}Indexer PUBLIC ${PROJECT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
