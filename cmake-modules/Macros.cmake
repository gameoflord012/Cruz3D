macro(find_all_sources NAME)
file(GLOB_RECURSE SOURCES
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
if(SOURCES) 
	list(APPEND "${NAME}" "${SOURCES}")
endif(SOURCES)
endmacro(find_all_sources)

macro(copy_target_dlls TARGET)
add_custom_command(TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:${TARGET}> $<TARGET_FILE_DIR:${TARGET}>
  COMMAND_EXPAND_LISTS
)
endmacro(copy_target_dlls)