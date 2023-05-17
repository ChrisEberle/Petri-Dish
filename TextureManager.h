#pragma once
class TextureManager
{
public:
	static void load_all_textures() {
	}
	static unsigned int loadTextureJPEG(const char* imagePath);
	static unsigned int loadTexturePNG(const char* imagePath);
	static void textureAnimation(unsigned int textArray[], int sizeOfArray, int width, int height, float xPos, float yPos, int speed);
private:
};