#pragma once

#ifdef CRUZ3D_IMPL
#define SOKOL_IMPL
#define SOKOL_GLCORE
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_log.h"
#undef SOKOL_APP_IMPL
#undef SOKOL_GFX_IMPL
#undef SOKOL_GLUE_IMPL
#undef SOKOL_LOG_IMPL
#undef SOKOL_IMPL
#undef SOKOL_GLCORE
#endif