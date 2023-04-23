cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(libraries)
add_subdirectory(wrapper)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
PRIVATE
test.cpp
benchmark.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE OMPEval OMPEvalWrapper)
