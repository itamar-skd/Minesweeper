set(CONFIG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp
)

list(SORT CONFIG_SOURCES)

add_library(config STATIC
    ${CONFIG_SOURCES}
)

target_include_directories(config PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)