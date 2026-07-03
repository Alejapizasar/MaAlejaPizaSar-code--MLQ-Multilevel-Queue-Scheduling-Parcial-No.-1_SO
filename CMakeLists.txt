cmake_minimum_required(VERSION 3.10)
project(MLQScheduler CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable useful warnings, consistent with how the project was developed/tested.
add_compile_options(-Wall -Wextra)

include_directories(include)

# Automatically pick up every .cpp file in src/, so new classes don't
# require manually editing this file each time.
file(GLOB SOURCES "src/*.cpp")

add_executable(mlq_scheduler ${SOURCES})
