set(USER_INTERFACE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/user_interface.cpp
)

list(SORT USER_INTERFACE_SOURCES)

add_library(user-interface STATIC
    ${USER_INTERFACE_SOURCES}
)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(user-interface
    PRIVATE
        game-matrix
        ${CURSES_LIBRARIES}
)

target_include_directories(user-interface PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)