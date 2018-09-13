cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

project(base64)

add_library(base64 STATIC base64.cc base64.h)