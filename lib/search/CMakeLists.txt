add_library(search STATIC
        Searcher.cpp
        Searcher.hpp
        QueryHandler.cpp
        QueryHandler.hpp
)

target_link_libraries(search PUBLIC index)

target_include_directories(search PUBLIC ${PROJECT_SOURCE_DIR})
