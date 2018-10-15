#ifndef __IMAGE_LOADER_HPP__
#define __IMAGE_LOADER_HPP__

#include <memory>
#include <string>
#include<cstdint>
#include "glm/glm.hpp"

#ifdef DEBUG_MEMORY
#include <iostream>
#endif

namespace ng {
class ImageLoader {
    public:
        enum ImageType {
            none = 0,
            grey = 1,
            greya= 2,
            rgb  = 3,
            rgba = 4,
        };
        static std::unique_ptr<uint8_t, void(*)(void*)>
        LoadImageFromFile(const std::string&, glm::ivec2&, int&,
                          const ImageType = ImageType::rgba, const bool = true);
#ifdef DEBUG_MEMORY
    private:
        static void FreeImageData(void*);
#endif
};
}

#endif