find_package(Assimp REQUIRED)

include(Macros)
find_all_sources(_SOURCES)

add_library(cruz3d-common ${_SOURCES})

target_include_directories(cruz3d-common PUBLIC 
	.. 
	"${CRUZ_THIRDPARTY_DIR}/glm"
	"${CRUZ_THIRDPARTY_DIR}/sokol"
	"${ASSIMP_INCLUDE_DIRS}")

target_link_libraries(cruz3d-common PUBLIC
	"${ASSIMP_LIBRARIES}")