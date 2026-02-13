cmake_minimum_required(VERSION 4.1)
project(LabProgrammazioneC__)

set(CMAKE_CXX_STANDARD 20)

add_executable(LabProgrammazioneC__ main.cpp Activity.cpp)
add_executable(run_tests tests/TodoListTests.cpp)