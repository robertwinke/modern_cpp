cmake_minimum_required(VERSION 3.1.0)

project(empty_project)

include(GNUInstallDirs)

set(SRCS
    ${CMAKE_SOURCE_DIR}/src/move_semantics_main.cpp
)

set(PUBLIC_HEADERS

)

set(PRIVATE_HEADERS
)

find_package(Threads REQUIRED)

add_executable(empty_project ${SRCS} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

target_include_directories(empty_project
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_compile_options(empty_project
    PRIVATE
    -Wall -Wextra -pedantic -Wlogical-op -Wold-style-cast -Wuseless-cast -Wdouble-promotion -Wshadow -Wformat=2 -Wno-format-nonliteral -Weffc++
)

set_target_properties(empty_project
    PROPERTIES
    CXX_STANDARD 20
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

target_link_libraries(empty_project Threads::Threads)


