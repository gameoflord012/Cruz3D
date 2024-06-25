#include "Camera.h"

#include <glm/gtx/transform.inl>

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
    assert(fabs(glm::length(m_lookDir) - 1.0f) < 0.005);
#endif

    m_position += m_lookDir * v.z;
    m_position += UP * v.y;
    m_position += glm::cross(m_lookDir, UP) * v.x;

    ApplyChanges();
}

void cruz::Camera::Rotate(glm::vec3 rot)
{
    // clang-format off
    glm::mat4x4 rotation
    {
        1, 0, 0, 0, 
        0, 1, 0, 0, 
        0, 0, 1, 0, 
        0, 0, 0, 1
    };
    // clang-format on

    rotation = glm::rotate(rotation, rot.x, {1.0f, 0.0f, 0.0f});
    rotation = glm::rotate(rotation, rot.y, {0.0f, 1.0f, 0.0f});
    rotation = glm::rotate(rotation, rot.z, {0.0f, 1.0f, 1.0f});

    glm::vec4 homo = {m_lookDir.x, m_lookDir.y, m_lookDir.z, 1.0f};
    homo = rotation * homo;

    m_lookDir = {homo.x / homo.w, homo.y / homo.w, homo.z / homo.w};
    m_lookDir = glm::normalize(m_lookDir);

    ApplyChanges();
}

void cruz::Camera::ApplyChanges()
{
    m_proj = glm::perspective(1.0f, m_ratio, 0.01f, 10.0f);
    m_view = glm::lookAt(m_position, {m_position + m_lookDir}, UP);
}
