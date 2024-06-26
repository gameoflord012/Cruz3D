#pragma once

#include <glm/vec2.hpp>
#include <sokol/sokol_app.h>

#include <vector>

namespace cruz
{
class Input
{
  public:
    
    void Frame();
    void ProcessEvent(const sapp_event *event);

    uint32_t GetModifiers();

    bool IsKeyDown(sapp_keycode key) const;
    
    glm::vec2 GetMouseDelta() const;
    bool IsMouseMoving() const;
    bool IsMouseDown(sapp_mousebutton) const;

  private:
    bool m_mouseMoving{};
    glm::vec2 m_mouseDelta;


    uint32_t m_modifiers;
    bool m_keyStates[SAPP_KEYCODE_MENU + 1];
    bool m_mouseStates[SAPP_MOUSEBUTTON_MIDDLE + 1];
    std::vector<sapp_event> m_eventStack;
};

namespace singleton
{
extern cruz::Input Input;
}
} // namespace cruz

#define INPUT_INS cruz::singleton::Input