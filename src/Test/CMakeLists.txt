include(Macros)
find_all_sources(_SOURCES)

add_executable(cruz3d-test "${_SOURCES}")
target_compile_options(cruz3d-test PRIVATE "${CRUZ_CXX_FLAGS}")
target_include_directories(cruz3d-test PRIVATE "..")
target_link_libraries(cruz3d-test cruz3d-common)