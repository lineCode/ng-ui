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
        shader->use();

        glm::vec3 cubeSpeed[] = {
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
            glm::vec3( 0.01f,  0.02f,  0.03f),
        };

        while(!glfwWindowShouldClose(window.getWindow())) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            sin(glfwGetTime()) > 0 ? glBindTexture(GL_TEXTURE_2D, texture) : glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);

            glBindVertexArray(VAO);
            float angle = 0;
            for(int index = 0; index < 10; index++) {
                // glm::mat4 trans(1.0f);
                // trans = glm::rotate(trans, (float)sin(glfwGetTime()) / 10.0f, glm::vec3(0.5f, 0.25f, 1.0f));
                // trans = glm::translate(trans, location);

                glm::mat4 model(1.0f);
                cubePositions[index] += cubeSpeed[index];
                auto tmp = cubePositions[index];
                if(tmp.x > 1.0f || tmp.x < -1.0f) {
                    cubeSpeed[index].x = -cubeSpeed[index].x;
                    cubePositions[index].x = tmp.x < -1.0f ? -1.0f - tmp.x : 1.0f - tmp.x;
                }
                if(tmp.y > 1.0f || tmp.y < -1.0f) {
                    cubeSpeed[index].y = -cubeSpeed[index].y;
                    cubePositions[index].y = tmp.y < -1.0f ? -1.0f - tmp.y : 1.0f - tmp.y;
                }
                if(tmp.z > 3.0f || tmp.z < -3.0f) {
                    cubeSpeed[index].z = -cubeSpeed[index].z;
                    cubePositions[index].z = tmp.z < -3.0f ? -3.0f - tmp.z : 3.0f - tmp.z;
                }
                model = glm::translate(model, cubePositions[index]);
                model = glm::rotate(model, glm::radians(angle += 20.0f * sin(glfwGetTime())), glm::vec3(1.0f, 0.3f, 0.5f));

                glm::mat4 view(1.0f);
                view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

                glm::mat4 projection(1.0f);
                projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, -3.0f, 3.0f);

                glm::mat4 render(projection * view * model);

                unsigned int transformLoc = glGetUniformLocation(shader->id, "transform");
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(render));

                glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_INT, 0);
            }
            glfwSwapBuffers(window.getWindow());
            glfwPollEvents();
        }
    } catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}