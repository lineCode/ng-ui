#include <iostream>
#include <cmath>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "Window.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "std/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main(int argc, char **argv) {
    try {
        Window window(800, 600, "LearnOpenGL");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
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

        auto shader = std::make_unique<Shader>("../data/shader.vs", "../data/shader.fs");

        stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../data/cut.png", &width, &height, &nrChannels, 0);
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);

        unsigned char *data1 = stbi_load("../data/awesomeface.png", &width, &height, &nrChannels, 0);
        unsigned int texture1;
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data1);

        shader->use();
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);

        // glm::mat4 trans(1.0f);
        // trans = glm::scale( trans, glm::vec3(0.5, -0.5, 0.5f));
        // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        // vec = trans * vec;
        // std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

        // unsigned int transformLoc = glGetUniformLocation(shader->id, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // float* matrix = glm::value_ptr(trans);
        // for(int indexY = 0; indexY < 4; indexY++) {
        //     for(int indexX = 0; indexX < 4; indexX++) {
        //         std::cout << matrix[indexY * 4 + indexX] << " ";
        //     }
        //     std::cout << std::endl;
        // }

        unsigned int color = glGetUniformLocation(shader->id, "ourColor");
        glUniform4f(color, 0.0f, 1.0, 0.0f, 1.0f);
        glm::vec3 location(0.0);
        glm::vec3 speed(1.0f, -1.0f, 1.0f);
        glm::mat4 trans(1.0f);

        while(!glfwWindowShouldClose(window.getWindow())) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            sin(glfwGetTime()) > 0 ? glBindTexture(GL_TEXTURE_2D, texture) : glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);

            location += glm::vec3((float)sin(glfwGetTime()) / 10.0f, (float)sin(glfwGetTime()) / 10.0f, 0.0f) * speed;
            if(location.x > 0.5 || location.x < -0.5) {
                speed.x = -speed.x;
            }
            if(location.y > 0.5 || location.y < -0.5) {
                speed.y = -speed.y;
            }
            // std::cout << location.x << " " << location.y << " " << location.z << std::endl;

            trans = glm::rotate(trans, (float)sin(glfwGetTime()) / 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
            trans = glm::translate(trans, glm::vec3((float)sin(glfwGetTime()) / 10.0f, (float)sin(glfwGetTime()) / 10.0f, 0.0f) * speed);

            float* matrix = glm::value_ptr(trans);
            for(int indexY = 0; indexY < 4; indexY++) {
                for(int indexX = 0; indexX < 4; indexX++) {
                    std::cout << matrix[indexY * 4 + indexX] << " ";
                }
                std::cout << std::endl;
            }

            unsigned int transformLoc = glGetUniformLocation(shader->id, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}