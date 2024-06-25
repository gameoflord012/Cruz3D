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

private:
    void ApplyChanges();

    glm::vec3 m_position{};
    glm::vec3 m_lookDir{};

    float m_ratio{};
    
    glm::mat4x4 m_view{};
    glm::mat4x4 m_proj{};
};
}