#pragma once

#ifdef CRUZ_IMPL

#include "Graphic/Shader.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE

#include "sokol_app.h"
#undef SOKOL_APP_IMPL

#include "sokol_gfx.h"
#undef SOKOL_GFX_IMPL

#include "sokol_glue.h"
#undef SOKOL_GLUE_IMPL

#include "sokol_log.h"
#undef SOKOL_LOG_IMPL

#undef SOKOL_IMPL
#undef SOKOL_GLCORE

#endif // CRUZ_IMPL