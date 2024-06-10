file(GLOB_RECURSE SOURCE_FILES
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(cruz3d-common ${SOURCE_FILES})

target_include_directories(cruz3d-common PUBLIC 
	.. 
	"${CRUZ_THIRDPARTY_DIR}/glm"
	"${CRUZ_THIRDPARTY_DIR}/sokol")