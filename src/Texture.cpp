#include "Texture.hpp"

namespace ng {
Texture::Texture(const std::string& filePath, ImageLoader::ImageType type) :
    Texture(Image(filePath, type)) {
//TODO
}
Texture::Texture(const Image& image) : size(image.getSize()) {
    glGenTextures(COUNT, &this->data);
#ifdef DEBUG_MEMORY
    std::cout << "Gen texture " << this->data << std::endl;
#endif
    glBindTexture(GL_TEXTURE_2D, this->data);
    switch(image.getType()) {
    case ImageLoader::ImageType::rgb:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     this->size.x, this->size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData());
        break;
    case ImageLoader::ImageType::rgba:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     this->size.x, this->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData());
        break;
    default:
        break;
    };
    glGenerateMipmap(GL_TEXTURE_2D);
}
Texture::~Texture() {
    glDeleteTextures(COUNT, &this->data);
#ifdef DEBUG_MEMORY
    std::cout << "Delete texture " << this->data << std::endl;
#endif
}
const unsigned int Texture::getData() const {
    return this->data;
}
const glm::ivec2 Texture::getSize() const {
    return this->size;
}
}