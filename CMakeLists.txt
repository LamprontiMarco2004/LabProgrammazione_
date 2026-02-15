cmake_minimum_required(VERSION 3.20)
project(LabProgrammazioneCPlusPlus)

set(CMAKE_CXX_STANDARD 17)

# 1. LOGICA
add_library(app_logic TodoList.cpp TodoList.h Activity.h Activity.cpp)

# 2. MAIN
add_executable(MainApp main.cpp TodoList.cpp Activity.cpp)
target_link_libraries(MainApp app_logic)

# 3. SCARICA GOOGLE TEST AUTOMATICAMENTE (Così ignoro la cartella lib)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. TEST
enable_testing()
add_executable(runTests Tests/TodoListTests.cpp)
target_link_libraries(runTests gtest_main app_logic)

include(GoogleTest)
gtest_discover_tests(runTests)