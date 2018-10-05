#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <string>
#include <stdexcept>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {
    public:
        Window(int, int, std::string);
        ~Window();
        GLFWwindow *getWindow();
    private:
        GLFWwindow *window;
        int width;
        int height;

        static void frameBufferSizeCallback(GLFWwindow *, int, int);
};

#endif