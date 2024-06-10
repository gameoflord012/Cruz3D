#include <ctime>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    try
    {
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

        glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);

        // Up vector (defines the "up" direction of the camera)
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        // Calculate the lookAt matrix
        glm::mat4 viewMatrix = glm::lookAt(cameraPos, targetPos, up);

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return EXIT_SUCCESS;
}