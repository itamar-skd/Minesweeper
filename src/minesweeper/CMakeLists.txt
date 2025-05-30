set(GAME_MATRIX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/game_matrix.cpp
)

list(SORT GAME_MATRIX_SOURCES)

add_library(game-matrix STATIC
    ${GAME_MATRIX_SOURCES}
)

target_include_directories(game-matrix PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)