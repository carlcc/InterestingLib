cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

project(sigslot)


add_library(sigslot sigslot.cc sigslot.h)