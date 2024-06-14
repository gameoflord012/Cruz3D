macro(find_all_sources NAME)
file(GLOB_RECURSE SOURCES
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
if(SOURCES) 
	list(APPEND "${NAME}" "${SOURCES}")
endif(SOURCES)
endmacro(find_all_sources)