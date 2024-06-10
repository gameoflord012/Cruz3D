#define CRUZ3D_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ3D_IMPL

#include <glm/gtc/matrix_transform.hpp>

static void sokol_init()
{
    sg_setup({
        .logger = {.func = slog_func},
        .environment = sglue_environment(),
    });
}

static void sokol_frame()
{
}

static void sokol_cleanup()
{
    sg_shutdown();
}

static void sokol_event(const sapp_event *)
{
}

sapp_desc sokol_main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    return {.init_cb = sokol_init,
            .frame_cb = sokol_frame,
            .cleanup_cb = sokol_cleanup,
            .event_cb = sokol_event,
            .width = 640,
            .height = 480,
            .logger = {.func = slog_func}};
}