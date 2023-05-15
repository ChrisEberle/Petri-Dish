#pragma once
class IMGUIUI
{
public:
	static void init_scene(GLFWwindow* window);
	static void clean_scene();
	static void ui_tools(std::string str, float& var1, float& var2, float& var3, float& var4, float& var5, Mix_Music* music);
private:
};