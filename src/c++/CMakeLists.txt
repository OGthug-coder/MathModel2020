cmake_minimum_required(VERSION 3.1)
project(MathModel2020 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


set(MYLIB_HEADERS
	double_pendulum.hpp
    )

#add_library(libusv ${MYLIB_HEADERS})

add_executable(myprogram main.cpp)