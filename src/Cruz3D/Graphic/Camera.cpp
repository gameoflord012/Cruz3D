#include "Camera.h"

#include <cassert>

cruz::Camera::Camera(float ratio)
{
    m_ratio = ratio;

    m_position = {0.0f, 0.0f, 2.0f};
    m_lookDir = {0.0f, 0.0f, -1.0f};

    ApplyChanges();
}

glm::mat4x4 cruz::Camera::GetProjView()
{
    return m_proj * m_view;
}

void cruz::Camera::Move(glm::vec3 v)
{
    m_position += v;
    ApplyChanges();
}

void cruz::Camera::MoveRel(glm::vec3 v)
{
#if _DEBUG
    assert(glm::length(m_lookDir) - 1.0f < glm::epsilon<float>());
#endif

    m_position += m_lookDir * v.z;
    m_position += UP * v.y;
    m_position += glm::cross(m_lookDir, UP) * v.x;

    ApplyChanges();
}

void cruz::Camera::ApplyChanges()
{
    m_proj = glm::perspective(1.0f, m_ratio, 0.01f, 10.0f);
    m_view = glm::lookAt(m_position, {m_position + m_lookDir}, UP);
}
