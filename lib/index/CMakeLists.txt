add_library(index STATIC
        Indexer.cpp
        Indexer.hpp
        Index.cpp
        Index.hpp
)

target_include_directories(index PUBLIC ${PROJECT_SOURCE_DIR})
