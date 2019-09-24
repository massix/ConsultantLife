cmake_minimum_required(VERSION 3.8)

project(ConsultantLife)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(core)
add_subdirectory(model)
add_subdirectory(resources)

add_executable(ConsultantLife main.cpp)
target_link_libraries(ConsultantLife core model)

