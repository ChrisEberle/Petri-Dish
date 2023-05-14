#include "Engine.h"

unsigned int TextureManager::loadTexture(const char* imagePath)
{
    int widthImg, heightImg, channels;
    unsigned char* image = stbi_load(imagePath, &widthImg, &heightImg, &channels, 0);
    if (image) {
        // Generate and bind the texture
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture parameters for mipmapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Set the base level texture data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        // Generate mipmaps manually
        int levels = static_cast<int>(std::floor(std::log2(std::max(widthImg, heightImg))) + 1);
        for (int level = 1; level < levels; level++) {
            int levelWidth = std::max(1, widthImg >> level);
            int levelHeight = std::max(1, heightImg >> level);
            unsigned char* levelData = resizeImageData(image, widthImg, heightImg, levelWidth, levelHeight);
            glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, levelWidth, levelHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, levelData);
            delete[] levelData;
        }

        // Free the loaded image data
        stbi_image_free(image);
        std::cout << "Successfully loaded texture: " << imagePath << std::endl;
        return textureID;
    }
    else {
        std::cout << "Failed to load texture: " << imagePath << std::endl;
        return 0; // Return 0 to indicate failure
    }
}

unsigned char* TextureManager::resizeImageData(const unsigned char* imageData, int srcWidth, int srcHeight, int dstWidth, int dstHeight)
{
    unsigned char* resizedData = new unsigned char[dstWidth * dstHeight * 3];
    float scaleX = static_cast<float>(srcWidth) / dstWidth;
    float scaleY = static_cast<float>(srcHeight) / dstHeight;

    for (int y = 0; y < dstHeight; ++y) {
        for (int x = 0; x < dstWidth; ++x) {
            int srcX = static_cast<int>(x * scaleX);
            int srcY = static_cast<int>(y * scaleY);

            // Accumulate the pixel values within the filter window
            float accumR = 0.0f;
            float accumG = 0.0f;
            float accumB = 0.0f;

            for (int fy = 0; fy < 2; ++fy) {
                for (int fx = 0; fx < 2; ++fx) {
                    int sampleX = srcX + fx;
                    int sampleY = srcY + fy;

                    // Wrap around for out-of-bounds samples
                    sampleX = (sampleX < 0) ? srcWidth - 1 : (sampleX >= srcWidth) ? 0 : sampleX;
                    sampleY = (sampleY < 0) ? srcHeight - 1 : (sampleY >= srcHeight) ? 0 : sampleY;

                    int sampleIndex = (sampleY * srcWidth + sampleX) * 3;
                    accumR += imageData[sampleIndex];
                    accumG += imageData[sampleIndex + 1];
                    accumB += imageData[sampleIndex + 2];
                }
            }

            // Compute the average pixel value within the filter window
            float averageR = accumR / 4.0f;
            float averageG = accumG / 4.0f;
            float averageB = accumB / 4.0f;

            // Assign the average value to the resized pixel
            int dstIndex = (y * dstWidth + x) * 3;
            resizedData[dstIndex] = static_cast<unsigned char>(averageR);
            resizedData[dstIndex + 1] = static_cast<unsigned char>(averageG);
            resizedData[dstIndex + 2] = static_cast<unsigned char>(averageB);
        }
    }

    return resizedData;
}
