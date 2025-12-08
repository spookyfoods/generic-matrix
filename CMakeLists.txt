cmake_minimum_required(VERSION 3.15...4.1)
project(MatrixProject VERSION 1.0
                  DESCRIPTION "Awesomesauce Project"
                  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  #
add_executable(main main.cpp)
