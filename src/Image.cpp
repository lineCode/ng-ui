#include "Image.hpp"

namespace ng {
Image::Image(const std::string& filePath, ImageLoader::ImageType type):
    filePath(filePath), data(nullptr, nullptr), type(type) {
    this->data = ImageLoader::LoadImageFromFile(
                     this->filePath, this->size, this->channel, this->type);
}

const uint8_t* Image::getData() const {
    return this->data.get();
}

const glm::ivec2 Image::getSize() const {
    return this->size;
}

const int Image::getChannel() const {
    return this->channel;
}

const ImageLoader::ImageType Image::getType() const {
    return this->type;
}
}