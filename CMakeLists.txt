cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(cpp/base64)
add_subdirectory(cpp/sigslot)

include_directories(
        cpp
)

add_subdirectory(cpptest)