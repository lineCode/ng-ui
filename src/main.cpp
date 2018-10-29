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
#include "Box.hpp"

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

void clean() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);
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

void drawBox(Shader* shader, glm::mat4 projection, ng::Camera& camera) {
    float angle = 0;
    shader->use();
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);
    unsigned int color = glGetUniformLocation(shader->id, "ourColor");
    glUniform4f(color, 0.7f, 1.0f, 0.5f, 1.0f);
    unsigned int lightColor = glGetUniformLocation(shader->id, "lightColor");
    glUniform4f(lightColor, cos(glfwGetTime()), sin(glfwGetTime()), 1.0f, 1.0f);
    unsigned int lightPos = glGetUniformLocation(shader->id, "lightPos");
    glUniform3f(lightPos, 2.0f,  5.0f, -15.0f);
    unsigned int viewPos = glGetUniformLocation(shader->id, "viewPos");
    auto cameraPos = camera.getPos();
    glUniform3f(viewPos, cameraPos.x, cameraPos.y, cameraPos.z);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  0.0f));
    model = glm::rotate(model, glm::radians(angle += 20.0f * sin(glfwGetTime())), glm::vec3(1.0f, 0.3f, 0.5f));
    glm::mat4 render(projection * camera.getView() * model);
    unsigned int transformLoc = glGetUniformLocation(shader->id, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(render));
    unsigned int modelLoc = glGetUniformLocation(shader->id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);
}

void drawLight(Shader* shaderLight, glm::mat4 projection, ng::Camera& camera) {
    float angle = 0;
    shaderLight->use();
    shaderLight->setInt("texture1", 0);
    shaderLight->setInt("texture2", 1);
    unsigned int lightColor = glGetUniformLocation(shaderLight->id, "lightColor");
    glUniform4f(lightColor, cos(glfwGetTime()), sin(glfwGetTime()), 1.0f, 1.0f);

    glm::mat4 modelLight(1.0f);
    modelLight = glm::translate(modelLight, glm::vec3( 2.0f,  5.0f, -15.0f));
    modelLight = glm::rotate(modelLight, glm::radians(angle += 20.0f * sin(glfwGetTime())), glm::vec3(1.0f, 0.3f, 0.5f));
    glm::mat4 render = projection * camera.getView() * modelLight;
    unsigned int transformLoc = glGetUniformLocation(shaderLight->id, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(render));
    glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);
}

int main(int argc, char **argv) {
    const std::string ROOT_PATH(argc < 1 ? "." : argv[1]);
    try {
        Window window(800, 600, "LearnOpenGL");

        auto shader = std::make_unique<Shader>(ROOT_PATH + "/data/shader/box.vs", ROOT_PATH + "/data/shader/box.fs");
        ng::Texture textureCut(ROOT_PATH + "/data/image/wall.jpg", ng::ImageLoader::ImageType::rgb);
        ng::Texture textureFace(ROOT_PATH + "/data/image/awesomeface.png", ng::ImageLoader::ImageType::rgba);
        auto shaderLight = std::make_unique<Shader>(ROOT_PATH + "/data/shader/light.vs", ROOT_PATH + "/data/shader/light.fs");

        glEnable(GL_DEPTH_TEST);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
        glfwSetScrollCallback(window.getWindow(), scroll_callback);
        glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int cout = 0;
        double start = 0;
        Box box;
        while(!glfwWindowShouldClose(window.getWindow())) {

            start = glfwGetTime();
            glfwWaitEventsTimeout(FPS);

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            float cameraSpeed = 2.5f * deltaTime;
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


            glBindTexture(GL_TEXTURE_2D, textureCut.getData());

            box.bindVertexArray();

            clean();

            drawLight(shaderLight.get(), projection, camera);
            drawBox(shader.get(), projection, camera);

            glfwSwapBuffers(window.getWindow());
        }
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}