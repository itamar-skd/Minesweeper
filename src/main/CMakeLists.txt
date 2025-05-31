add_executable(minesweeper main.cpp)

target_link_libraries(minesweeper
    PRIVATE
        utilities
        game-matrix
        user-interface
)