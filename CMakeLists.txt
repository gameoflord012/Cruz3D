cmake_minimum_required (VERSION 3.8)
project (Cruz3D)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

set(CRUZ_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "/W4;/std:c++20")
set(CRUZ_THIRDPARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")
set(CRUZ_LIBS_DIR "${PROJECT_SOURCE_DIR}/thirdparty/libs")

add_subdirectory("src")
