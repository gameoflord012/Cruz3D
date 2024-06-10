file(GLOB_RECURSE SOURCE_FILES
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(cruz3d-test "${SOURCE_FILES}")
target_include_directories(cruz3d-test PRIVATE "..")
target_link_libraries(cruz3d-test cruz3d-common)