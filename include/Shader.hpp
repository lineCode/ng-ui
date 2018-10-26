#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
    public:
        Shader(std::string, std::string);
        void use();
        void setBool(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const {
            glUniform1i(glGetUniformLocation(id, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const {
            glUniform1f(glGetUniformLocation(id, name.c_str()), value);
        }
        void setVec3(const std::string &name, glm::vec3 value) const {
            glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
        }
        void setMat4(const std::string &name, glm::mat4 value) const {
            glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
        }
    public:
        unsigned int id;
};

#endif