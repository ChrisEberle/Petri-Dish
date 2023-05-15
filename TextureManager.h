#pragma once
class TextureManager
{
public:
	static void load_all_textures() {

	}
	static unsigned int loadTexture(const char* imagePath);
private:
	static unsigned char* resizeImageData(const unsigned char* imageData, int srcWidth, int srcHeight, int dstWidth, int dstHeight);
};