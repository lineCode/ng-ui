#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "Window.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ImageLoader.hpp"
#include "Image.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

double const FPS = 1 / 25.0f;

ng::Camera camera(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f,  0.0f));

bool firstMouse = false;
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    camera.rotate(yaw, pitch);
}

int main(int argc, char **argv) {
    for(int index = 0; index < argc; index++) {
        std::cout << argv[index] << std::endl;
    }
    const std::string ROOT_PATH(argv[1]);
    try {
        Window window(800, 600, "LearnOpenGL");

        float vertices[] = {
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

            0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 2, 1, 0, 2, 3,
            4, 6, 5, 4, 6, 7,
            8, 10, 9, 8, 10, 11,
            12, 14, 13, 12, 14, 15,
            16, 18, 17, 16, 18, 19,
            20, 22, 21, 20, 22, 23,
        };

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(2);

        std::cout << ROOT_PATH + "/data/box.vs" << std::endl;
        auto shader = std::make_unique<Shader>(ROOT_PATH + "/data/box.vs", ROOT_PATH + "/data/box.fs");
        ng::Texture textureCut(ROOT_PATH + "/data/wall.jpg", ng::ImageLoader::ImageType::rgb);
        ng::Texture textureFace(ROOT_PATH + "/data/awesomeface.png", ng::ImageLoader::ImageType::rgba);

        auto shaderLight = std::make_unique<Shader>(ROOT_PATH + "/data/light.vs", ROOT_PATH + "/data/light.fs");
        // ng::Texture textureCut("../data/wall.jpg", ng::ImageLoader::ImageType::rgb);
        // ng::Texture textureFace("../data/awesomeface.png", ng::ImageLoader::ImageType::rgba);

        glEnable(GL_DEPTH_TEST);

        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        float deltaTime = 0.0f; // Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame

        glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
        glfwSetScrollCallback(window.getWindow(), scroll_callback);
        glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int cout = 0;
        double start = 0;
        while(!glfwWindowShouldClose(window.getWindow())) {

            // std::cout << "Wait " << 1.0f / (glfwGetTime() - start) << cout++ << std::endl;
            start = glfwGetTime();
            glfwWaitEventsTimeout(FPS);

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
            if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
                camera.move(cameraSpeed, 0);
            }
            if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
                camera.move(-cameraSpeed, 0);
            }
            if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
                camera.move(0, -cameraSpeed);
            }
            if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
                camera.move(0, cameraSpeed);
            }

            glm::mat4 projection(1.0f);
            projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            // sin(glfwGetTime()) > 0 ? glBindTexture(GL_TEXTURE_2D, textureFace.getData()) : glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textureCut.getData());

            glBindVertexArray(VAO);
            float angle = 0;

            // for(int index = 0; index < 1; index++) {
            shader->use();
            shader->setInt("texture1", 0);
            shader->setInt("texture2", 1);
            unsigned int color = glGetUniformLocation(shader->id, "ourColor");
            glUniform4f(color, 0.7f, 1.0f, 0.5f, 1.0f);
            unsigned int lightColor = glGetUniformLocation(shader->id, "lightColor");
            glUniform4f(lightColor, cos(glfwGetTime()), sin(glfwGetTime()), 1.0f, 1.0f);

            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[0]);
            model = glm::rotate(model, glm::radians(angle += 20.0f * sin(glfwGetTime())), glm::vec3(1.0f, 0.3f, 0.5f));
            glm::mat4 render(projection * camera.getView() * model);
            unsigned int transformLoc = glGetUniformLocation(shader->id, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(render));

            glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);
            // }

            shaderLight->use();
            shaderLight->setInt("texture1", 0);
            shaderLight->setInt("texture2", 1);
            // unsigned int color = glGetUniformLocation(shader->id, "ourColor");
            // glUniform4f(color, 0.0f, 1.0f, 0.0f, 1.0f);
            lightColor = glGetUniformLocation(shaderLight->id, "lightColor");
            glUniform4f(lightColor, cos(glfwGetTime()), sin(glfwGetTime()), 1.0f, 1.0f);

            glm::mat4 modelLight(1.0f);
            modelLight = glm::translate(modelLight, cubePositions[1]);
            modelLight = glm::rotate(modelLight, glm::radians(angle += 20.0f * sin(glfwGetTime())), glm::vec3(1.0f, 0.3f, 0.5f));
            render = projection * camera.getView() * modelLight;
            transformLoc = glGetUniformLocation(shaderLight->id, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(render));

            glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window.getWindow());
        }
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}