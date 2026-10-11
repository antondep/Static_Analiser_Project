cmake_minimum_required(VERSION 3.20)
project(StaticAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} ${CLANG_INCLUDE_DIRS} include)
add_definitions(${LLVM_DEFINITIONS})

add_executable(analyzer 
    src/parser.cpp
    src/rules/rule501.cpp
)

target_link_libraries(analyzer PRIVATE
    clangTooling
    clangFrontend
    clangAST
    clangBasic
)