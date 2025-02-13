cmake_minimum_required(VERSION 3.22)

project(WaddoupsHomework2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OpenMP required 
find_package(OpenMP)

# Fmt Lib
# include(FetchContent)
# FetchContent_Declare(
#   fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt
#   GIT_TAG        9cf9f38eded63e5e0fb95cd536ba51be601d7fa2)
# FetchContent_MakeAvailable(fmt)

# Maximum Compiler Warnings
include(CompilerWarnings.cmake)
waddoups_set_project_warnings()

include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRCS src/count_sort_reference.cpp src/count_sort.cpp)

# Optimization Flags
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) # LTO
set(OPTS -DNDEBUG -O3)
# set(OPTS -DDEBUG -O0 -g3) # uncomment for debug

# Command line interface application
add_executable(cli cli.cpp ${SRCS})
# target_link_libraries(cli fmt::fmt)
target_compile_options(cli PRIVATE ${OPTS})
if(OpenMP_CXX_FOUND)
    target_link_libraries(cli PUBLIC OpenMP::OpenMP_CXX)
endif()

