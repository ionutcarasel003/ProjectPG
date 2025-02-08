#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->yaw = -90.0f;    
        this->pitch = 0.0f;   
        this->isMouseActive = false; 
        this->lastX = 400;    
        this->lastY = 300;    
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontDirection = glm::normalize(direction);

        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        glm::vec3 forward = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 right = glm::normalize(glm::cross(forward, cameraUpDirection));
        glm::vec3 up = glm::normalize(glm::cross(right, forward));

        switch (direction) {
            case MOVE_FORWARD:
                cameraPosition += forward * speed;
                cameraTarget += forward * speed;
                break;
            case MOVE_BACKWARD:
                cameraPosition -= forward * speed;
                cameraTarget -= forward * speed;
                break;
            case MOVE_LEFT:
                cameraPosition -= right * speed;
                cameraTarget -= right * speed;
                break;
            case MOVE_RIGHT:
                cameraPosition += right * speed;
                cameraTarget += right * speed;
                break;
            case MOVE_UP:
                cameraPosition += up * speed;
                cameraTarget += up * speed;
                break;
            case MOVE_DOWN:
                cameraPosition -= up * speed;
                cameraTarget -= up * speed;
                break;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        this->yaw += yaw;
        this->pitch += pitch;

        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        direction.y = sin(glm::radians(this->pitch));
        direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->cameraTarget = this->cameraPosition + glm::normalize(direction);
    }
}
