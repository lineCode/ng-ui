#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
    public:
        unsigned int id;
};

#endif