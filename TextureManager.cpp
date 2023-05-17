#include "Engine.h"

unsigned int TextureManager::loadTextureJPEG(const char* imagePath)
{
    int widthImg, heightImg, channels;
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically
    unsigned char* image = stbi_load(imagePath, &widthImg, &heightImg, &channels, 0);
    if (!image) {
        std::cout << "Failed to load texture: " << imagePath << std::endl;
        return 0; // Return 0 to indicate failure
    }

    // Generate and bind the texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Free the loaded image data
    stbi_image_free(image);
    std::cout << "Successfully loaded texture: " << imagePath << std::endl;
    return textureID;
}

unsigned int TextureManager::loadTexturePNG(const char* imagePath)
{
    int widthImg, heightImg, channels;
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically
    unsigned char* image = stbi_load(imagePath, &widthImg, &heightImg, &channels, STBI_rgb_alpha);
    if (!image) {
        std::cout << "Failed to load texture: " << imagePath << std::endl;
        return 0; // Return 0 to indicate failure
    }

    // Generate and bind the texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Free the loaded image data
    stbi_image_free(image);
    std::cout << "Successfully loaded texture: " << imagePath << std::endl;
    return textureID;
}

void TextureManager::textureAnimation(unsigned int textArray[], int sizeOfArray, int width, int height, float xPos, float yPos, int speed)
{
    static int counter = 0; // static variable to remember the current counter
    int textureIndex = (counter / (speed / sizeOfArray)) % sizeOfArray;

    Graphics::drawTexture(textArray[textureIndex], width, height, xPos, yPos);

    counter++;
    if (counter >= speed * sizeOfArray) {
        counter = 0;
    }
}
