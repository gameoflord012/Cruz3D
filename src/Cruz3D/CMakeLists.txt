find_package(Assimp REQUIRED)

include(Macros)
find_all_sources(_SOURCES)

add_library(cruz3d-static ${_SOURCES})

add_dependencies(cruz3d-static compile-shaders)

target_compile_definitions(cruz3d-static 
	PUBLIC "CRUZ_DATA_DIR=\"${CRUZ_DATA_DIR}\"")

target_include_directories(cruz3d-static PUBLIC 
	.. 
	"${CRUZ_THIRDPARTY_DIR}"
	"${ASSIMP_INCLUDE_DIRS}")
	
target_link_libraries(cruz3d-static PUBLIC
	"${ASSIMP_LIBRARIES}")