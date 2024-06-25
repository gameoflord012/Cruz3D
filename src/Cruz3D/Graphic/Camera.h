#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace cruz
{
class Camera
{
public:
    Camera(float ratio);

    glm::mat4x4 GetProjView();

    void Move(glm::vec3);
    void MoveRel(glm::vec3);

private:
    const glm::vec3 UP = {0, 1, 0};

    void ApplyChanges();

    glm::vec3 m_position{};
    glm::vec3 m_lookDir{};

    float m_ratio{};
    
    glm::mat4x4 m_view{};
    glm::mat4x4 m_proj{};
};
}