set(ASSIMP_LIBRARIES "${CRUZ_LIBS_DIR}/assimp-vc143-mt.lib")
set(ASSIMP_INCLUDE_DIRS "${CRUZ_THIRDPARTY_DIR}/assimp")

if(NOT TARGET Assimp::Static)
    add_library(Assimp::Static IMPORTED STATIC)
    set_target_properties(Assimp::Static PROPERTIES IMPORTED_LOCATION "${ASSIMP_LIBRARIES}")
    target_include_directories(Assimp::Static INTERFACE "${ASSIMP_INCLUDE_DIRS}")
endif()