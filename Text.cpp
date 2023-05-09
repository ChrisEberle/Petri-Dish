#include "Engine.h"

TextRenderer::TextRenderer() {}

TextRenderer::TextRenderer(int height)
	: height(height) {}

bool TextRenderer::loadFont(FT_Library& ft, std::string path) {

}

void render(GLFWwindow* window, std::string text, float xPos, float yPos, float scale, const float* color) {

}

void TextRenderer::cleanup() {

}