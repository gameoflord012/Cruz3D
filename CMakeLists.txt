cmake_minimum_required (VERSION 3.8)
project (Cruz3D)

set(CRUZ_DATA_DIR		"${PROJECT_SOURCE_DIR}/data")
set(CRUZ_THIRDPARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(
	"/W4" "/WX" 
	"$<$<CONFIG:Debug>:/ZI>")
add_link_options("$<$<CONFIG:Debug>:/INCREMENTAL>")


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${PROJECT_BINARY_DIR}/bin)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory("src")