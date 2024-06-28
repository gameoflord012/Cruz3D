# > ./sokol-shdc --input shd.glsl --output shd.h --slang glsl430:hlsl5:metal_macos
include(Macros)

set(_SLANG "glsl430")

macro(recurse_folder VAR DIR GLOBEXPR)
  file(GLOB_RECURSE _SHADER_FILES
    RELATIVE "${DIR}"
    CONFIGURE_DEPENDS 
    "${GLOBEXPR}")
endmacro(recurse_folder)

recurse_folder(_SHADER_FILES "" "*.glsl")

foreach(SHADER IN LISTS _SHADER_FILES)
    add_custom_command(
        OUTPUT "${SHADER}.h"
        COMMAND ${CRUZ_TOOLS_DIR}/sokol-shdc.exe --input ${SHADER} --output ${SHADER}.h --slang ${_SLANG}
        DEPENDS ${SHADER}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    list(APPEND _SHADER_OUTPUTS "${SHADER}.h")
endforeach()

add_custom_target(compile-shaders
    DEPENDS "${_SHADER_OUTPUTS}"
)