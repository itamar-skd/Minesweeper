set(UTILITIES_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/print_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/arg_utils.cpp
)

list(SORT UTILITIES_SOURCES)

add_library(utilities STATIC
    ${UTILITIES_SOURCES}
)

target_link_libraries(utilities
    PRIVATE
        game-matrix
)

target_include_directories(utilities PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)