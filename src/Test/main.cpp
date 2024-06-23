#include "assimp_test.h"

sapp_desc sokol_main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    return {.init_cb = sokol_init,
            .frame_cb = sokol_frame,
            .cleanup_cb = sokol_cleanup,
            // .event_cb = sokol_event,
            .width = 640,
            .height = 480,
            .logger = {.func = slog_func}};
}