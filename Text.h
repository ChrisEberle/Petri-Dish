#ifndef TEXT_H
#include FT_FREETYPE_H

typedef struct {
	unsigned int textureId; // texture id storing character
	glm::ivec2 size; // size of char
	glm::ivec2 bearing; // distance from origin to top left of char
	unsigned int advance; // distance from origin to next origin
} Character;

class TextRenderer {
public:
	TextRenderer();
	TextRenderer(int height);

	bool loadFont(FT_Library& ft, std::string path);

	void render(GLFWwindow* window, std::string text, float xPos, float yPos, float scale, const float* color);

	void cleanup();

private:
	int height;
	FT_Face fontface;

	std::map<char, Character> chars;

	GLuint VAO;

};

#endif // !TEXT_H