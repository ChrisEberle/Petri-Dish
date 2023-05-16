#pragma once
class TextureManager
{
public:
	static void load_all_textures() {
	}
	static unsigned int loadTextureJPEG(const char* imagePath);
	static unsigned int loadTexturePNG(const char* imagePath);
private:
};