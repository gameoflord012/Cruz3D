#include "Input.h"

#include <Cruz3D/Debug.h>

#include <glm/glm.hpp>

// singleton pattern
cruz::Input cruz::singleton::Input;

void cruz::Input::Frame()
{
    m_mouseDelta = {0.0f, 0.0f};
    m_mouseMoving = false;

    while (!m_eventStack.empty())
    {
        const sapp_event &evt = m_eventStack.back();
        {
            m_modifiers = evt.modifiers;

            if (evt.type == SAPP_EVENTTYPE_KEY_DOWN)
            {
                m_keyStates[evt.key_code] = true;
            }

            if (evt.type == SAPP_EVENTTYPE_KEY_UP)
            {
                m_keyStates[evt.key_code] = false;
            }

            if (evt.type == SAPP_EVENTTYPE_MOUSE_DOWN)
            {
                m_mouseStates[evt.mouse_button] = true;
            }

            if (evt.type == SAPP_EVENTTYPE_MOUSE_UP)
            {
                m_mouseStates[evt.mouse_button] = false;
            }

            if (evt.type == SAPP_EVENTTYPE_MOUSE_MOVE)
            {
                m_mouseDelta = {evt.mouse_dx, evt.mouse_dy};
                m_mouseMoving = true;
            }
        }
        m_eventStack.pop_back();
    }
}

void cruz::Input::ProcessEvent(const sapp_event *event)
{
    m_eventStack.emplace_back(*event);
}

uint32_t cruz::Input::GetModifiers()
{
    return m_modifiers;
}

glm::vec2 cruz::Input::GetMouseDelta() const
{
    return m_mouseDelta;
}

bool cruz::Input::IsMouseMoving() const
{
    return m_mouseMoving;
}

bool cruz::Input::IsMouseDown(sapp_mousebutton mbtn) const
{
    return m_mouseStates[mbtn];
}

bool cruz::Input::IsKeyDown(sapp_keycode key) const
{
    return m_keyStates[key];
}
