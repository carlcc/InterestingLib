cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

project(aes)

add_library(aes STATIC AESCodec.h AESCodec.cpp)