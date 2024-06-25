#include "Input.h"

// singleton pattern
cruz::Input cruz::singleton::Input;

void cruz::Input::ProcessEvent(const sapp_event *event)
{
    if (event->type == SAPP_EVENTTYPE_KEY_DOWN)
    {
        m_keyStates[event->key_code] = true;
    }

    if (event->type == SAPP_EVENTTYPE_KEY_UP)
    {
        m_keyStates[event->key_code] = false;
    }

    if (event->type == SAPP_EVENTTYPE_MOUSE_DOWN)
    {
        m_mouseStates[event->mouse_button] = true;
    }

    if (event->type == SAPP_EVENTTYPE_MOUSE_UP)
    {
        m_mouseStates[event->mouse_button] = false;
    }

    if (event->type == SAPP_EVENTTYPE_MOUSE_MOVE)
    {
        m_mouseDelta = {event->mouse_dx, event->mouse_dy};
        m_mouseMoving = true;
    }
    else
    {
        m_mouseDelta = {0.0f, 0.0f};
        m_mouseMoving = false;
    }
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
