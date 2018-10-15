#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "ImageLoader.hpp"

namespace ng {
std::unique_ptr<uint8_t, void(*)(void*)> ImageLoader::LoadImageFromFile(const std::string& filePath,
                                                                        glm::ivec2& size, int& chanels,
                                                                        const ImageType type, bool isFlip) {
    stbi_set_flip_vertically_on_load(isFlip);
    uint8_t* data = stbi_load(filePath.c_str(), &size.x, &size.y, &chanels, static_cast<int>(type));
#ifdef DEBUG_MEMORY
    std::cout << "Load image " << static_cast<void*>(data) << std::endl;
    return std::unique_ptr<uint8_t, void(*)(void*)>(data, ImageLoader::FreeImageData);
#else
    return std::unique_ptr<uint8_t, void(*)(void*)>(data, stbi_image_free);
#endif
}
#ifdef DEBUG_MEMORY
void ImageLoader::FreeImageData(void* data) {
    std::cout << "Free image " << static_cast<void*>(data) << std::endl;
    stbi_image_free(data);
}
#endif
}