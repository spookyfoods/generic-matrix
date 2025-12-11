cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MatrixProject VERSION 1.0
                  DESCRIPTION "Awesomesauce Project"
                  LANGUAGES CXX)

add_executable(main main.cpp)

set_target_properties(main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(main PRIVATE /W4 /permissive-)
else()
    target_compile_options(main PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
    )
endif()

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
