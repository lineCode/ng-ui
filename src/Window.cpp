#include "Window.hpp"

Window::Window(int width, int height, std::string title) :
    width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
    if(!this->window) {
        throw std::runtime_error("Init Window");
    }
    glfwMakeContextCurrent(this->window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Init GLAD");
    }
    glViewport(0, 0, this->width, this->height);
    glfwSetFramebufferSizeCallback(this->window, Window::frameBufferSizeCallback);
    glViewport(0, 0, this->width, this->height);
}

void Window::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *Window::getWindow() {
    return this->window;
}

Window::~Window() {
    glfwTerminate();
}