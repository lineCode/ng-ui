#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <iostream>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace ng {
class Camera {
    public:
        Camera(glm::vec3, glm::vec3, glm::vec3);
        glm::vec3 getPos();
        glm::vec3 getFront();
        glm::vec3 getUp();
        glm::vec3 move(float, float);
        glm::vec3 rotate(float, float);
        glm::mat4 getView();
    private:
        glm::vec3 pos;
        glm::vec3 up;
        glm::vec3 front;
        glm::mat4 view;
};
}

#endif