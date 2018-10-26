#include "Camera.hpp"

namespace ng {
Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
    pos(pos), up(up), front(front), view(1.0f) {
    this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
}

glm::vec3 Camera::getPos() {
    return this->pos;
}

glm::vec3 Camera::getFront() {
    return this->front;
}

glm::vec3 Camera::getUp() {
    return this->up;
}

glm::vec3 Camera::move(float ws, float ad) {
    this->pos += ws * this->front;
    this->pos += glm::normalize(glm::cross(this->front, this->up)) * ad;
    this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
    return this->pos;
}

glm::vec3 Camera::rotate(float yaw, float pitch) {
    yaw = glm::radians(yaw);
    pitch = glm::radians(pitch);
    this->front.x = cos(yaw) * cos(pitch);
    this->front.y = sin(pitch);
    this->front.z = sin(yaw) * cos(pitch);
    this->front = glm::normalize(this->front);
    this->view = glm::lookAt(this->pos, this->pos + this->front, this->up);
}

glm::mat4 Camera::getView() {
    return this->view;
}
}