find_package(Assimp REQUIRED)

include(Macros)
find_all_sources(_SOURCES)

add_library(cruz3d-static)
target_compile_options(cruz3d-static PRIVATE "${CRUZ_CXX_FLAGS}")

target_sources(cruz3d-static PRIVATE ${_SOURCES})

target_include_directories(cruz3d-static PUBLIC 
	.. 
	"${CRUZ_THIRDPARTY_DIR}/glm"
	"${CRUZ_THIRDPARTY_DIR}/sokol"
	"${ASSIMP_INCLUDE_DIRS}")
	
target_link_libraries(cruz3d-static PUBLIC
	"${ASSIMP_LIBRARIES}")