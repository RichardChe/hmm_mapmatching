cmake_minimum_required(VERSION 3.1)

PROJECT(cpp_hmm_matching)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if(COMPILER_SUPPORTS_CXX11)
    add_definitions("-std=c++11")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB INMEM_MAP_LIST_CPP ${PROJECT_SOURCE_DIR}/lib/*.cpp)
add_library(libInMemMap SHARED ${INMEM_MAP_LIST_CPP})

add_executable(test_graph ${PROJECT_SOURCE_DIR}/src/example_graph.cpp)
target_link_libraries(test_graph libInMemMap)

