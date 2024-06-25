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
}

bool cruz::Input::IsKeyPressed(sapp_keycode key)
{
    return m_keyStates[key];
}
