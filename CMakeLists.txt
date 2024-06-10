cmake_minimum_required (VERSION 3.8)
project (Cruz3D)

set(CRUZ_THIRDPARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")
set(CRUZ_CXX_FLAGS "${CMAKE_CXX_FLAGS}" "/W4;/std:c++20")

add_subdirectory("src")
