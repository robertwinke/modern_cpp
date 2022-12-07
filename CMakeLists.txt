cmake_minimum_required(VERSION 3.1.0)

#set( CMAKE_CXX_COMPILER "C:\\mingw64\\bin\\g++" )
#set( CMAKE_C_COMPILER "C:\\mingw64\\bin\\gcc" )


project(empty_project)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/build)

include(GNUInstallDirs)

set(SRCS
    ${CMAKE_SOURCE_DIR}/src/main.cpp
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

# TODO: transfer options of the target lib?
if(NOT MSVC)
    target_compile_options(empty_project
        PRIVATE
        -Wall -Wextra -pedantic -Wlogical-op -Wold-style-cast -Wuseless-cast -Wdouble-promotion -Wshadow -Wformat=2 -Wno-format-nonliteral -Weffc++
)
endif()

if(NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -no-pie) # On modern distros PIE is enabled by default but libraries are compiled with -fPIC instead of -fPIE
endif()

set_target_properties(empty_project
    PROPERTIES
    CXX_STANDARD 20
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

target_link_libraries(empty_project Threads::Threads ${opencv_LIBS})


