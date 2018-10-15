#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <string>
#include "ImageLoader.hpp"
#include "Image.hpp"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#ifdef DEBUG_MEMORY
#include <iostream>
#endif

#define COUNT 1

namespace ng {
class Texture {
    public:
        Texture(const std::string&, ImageLoader::ImageType = ImageLoader::ImageType::rgba);
        Texture(const Image&);
        ~Texture();
        const unsigned int getData() const;
        const glm::ivec2 getSize() const;
    private:
        unsigned int data;
        glm::ivec2 size;
};
}

#endif