cmake_minimum_required(VERSION 3.20)

project(AsciiConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED
    COMPONENTS
    core
    imgproc
    imgcodecs
    videoio
)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(
    ascii_converter
    src/main.cpp
    src/AsciiConverter.cpp
)

target_link_libraries(
    ascii_converter
    PRIVATE
    ${OpenCV_LIBS}
)
