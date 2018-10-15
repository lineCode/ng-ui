#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <string>
#include "ImageLoader.hpp"
#include "glm/glm.hpp"

namespace ng {
class Image {
    public:
        Image(const std::string&, ImageLoader::ImageType = ImageLoader::ImageType::rgba);
        const uint8_t* getData() const;
        const glm::ivec2 getSize() const;
        const int getChannel() const;
        const ImageLoader::ImageType getType() const;
    private:
        const std::string filePath;
        std::unique_ptr<uint8_t, void(*)(void*)> data;
        glm::ivec2 size;
        int channel;
        const ImageLoader::ImageType type;
};
}

#endif