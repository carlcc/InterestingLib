cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

project(tests)

add_executable(TestSigSlot TestSigSlot.cpp)
target_link_libraries(TestSigSlot sigslot)

add_executable(TestAES TestAES.cpp)
target_link_libraries(TestAES aes)