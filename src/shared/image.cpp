/*
FILE: image.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
A thin wrapper to some pixels, and a way to save them to disk as an image
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include "image.h"
#include "color_spaces.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void SaveImage(const Image& image, const char* fileName)
{
    std::vector<PixelRGBAU8> rgbaU8;

    rgbaU8.resize(image.m_pixels.size());

    PixelRGBAU8* destPixel = rgbaU8.data();
    const PixelRGBAF32_PMA* srcPixel = image.m_pixels.data();
    for (size_t pixelIndex = 0, pixelCount = image.m_width*image.m_height; pixelIndex < pixelCount; ++pixelIndex, ++destPixel, ++srcPixel)
        *destPixel = PixelRGBAU8(*srcPixel);

    stbi_write_png(fileName, image.m_width, image.m_height, 4, rgbaU8.data(), image.m_width * sizeof(rgbaU8[0]));
}

void BlendInImage(Image& image, const Image& otherImage, int pastex, int pastey)
{
    int startX = Clamp(pastex, 0, image.m_width);
    int startY = Clamp(pastey, 0, image.m_height);

    int endX = Clamp(pastex + otherImage.m_width, 0, image.m_width);
    int endY = Clamp(pastey + otherImage.m_height, 0, image.m_height);

    for (int y = startY; y < endY; ++y)
    {
        // calculate starting pixel on image we are pasting in
        int srcX = startX - pastex;
        int srcY = y - pastey;
        const PixelRGBAF32_PMA* srcPixel = &otherImage.m_pixels[srcY * otherImage.m_width + srcX];

        // calculate starting pixel on image we are pasting to
        PixelRGBAF32_PMA* destPixel = &image.m_pixels[y * image.m_width + startX];

        // do a row of pasting
        for (int x = startX; x < endX; ++x, ++srcPixel, ++destPixel)
            destPixel->BlendIn(*srcPixel);
    }
}

void BlendInImage_Resize(Image& image, const Image& otherImage, unsigned int pastex, unsigned int pastey, PixelRGBAF32 clearColor)
{
    // make a new image large enough to hold both images, and fill it with the clear color
    int width = std::max(image.m_width, int(pastex) + otherImage.m_width);
    int height = std::max(image.m_height, int(pastey) + otherImage.m_height);
    Image newImage(width, height, clearColor);

    // blend in the first image
    BlendInImage(newImage, image, 0, 0);

    // blend in the second image
    BlendInImage(newImage, otherImage, pastex, pastey);

    // set the image to the new image
    image = newImage;
}
