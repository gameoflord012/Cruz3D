#pragma once

#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>

#ifdef CRUZ_IMPL

#include "Graphic/Shader.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE

#include <sokol_app.h>
#undef SOKOL_APP_IMPL

#undef SOKOL_IMPL
#undef SOKOL_GLCORE

#endif // CRUZ_IMPL