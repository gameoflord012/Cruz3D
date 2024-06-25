#pragma once

#include <glm/vec2.hpp>
#include <sokol/sokol_app.h>

#include <vector>

namespace cruz
{
class Input
{
  public:
    void ProcessEvent(const sapp_event *event);
    bool IsKeyDown(sapp_keycode key) const;
    
    glm::vec2 GetMouseDelta() const;
    bool IsMouseMoving() const;
    bool IsMouseDown(sapp_mousebutton) const;

  private:
    bool m_mouseMoving{};
    glm::vec2 m_mouseDelta;

    bool m_keyStates[SAPP_KEYCODE_MENU + 1];
    bool m_mouseStates[SAPP_MOUSEBUTTON_MIDDLE + 1];
};

namespace singleton
{
extern cruz::Input Input;
}
} // namespace cruz

#define INPUT_INS cruz::singleton::Input