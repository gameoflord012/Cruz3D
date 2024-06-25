#pragma once

#include <sokol/sokol_app.h>

namespace cruz
{
class Input
{
  public:
    void ProcessEvent(const sapp_event *event);
    bool IsKeyPressed(sapp_keycode key);
  private:
    bool m_keyStates[SAPP_KEYCODE_MENU + 1];
};

namespace singleton
{
extern cruz::Input Input;
}
} // namespace cruz