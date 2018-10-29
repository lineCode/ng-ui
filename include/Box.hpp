#ifndef __BOX_HPP__
#define __BOX_HPP__

#include <array>
#include "glad/glad.h"

#define SIZE_VERTICE 288
#define SIZE_INDECE 36

enum ObjectElement {
    Vertices = 0,
    Colors = 1,
    Textures = 2,
};

class Box {
    public:
        Box();
        ~Box();
        void changStateObjectElement(ObjectElement, bool = true);
        void bindVertexArray();
    private:
        const std::array<float, SIZE_VERTICE> vertices;
        const std::array<int, SIZE_INDECE> indices;
        unsigned int EBO;
        unsigned int VBO;
        unsigned int VAO;
        const ObjectElement objectElementVertives;
        const ObjectElement objectElementColor;
        const ObjectElement objectElementTextures;
};

#endif