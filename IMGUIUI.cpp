#include "Engine.h"

void IMGUIUI::init_scene(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void IMGUIUI::clean_scene()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void IMGUIUI::ui_tools(std::string str, float& var1, float& var2, float& var3, float& var4, float& var5)
{
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin(str.c_str());

    ImGui::Text("Modifiable Variables");
                                                                 
    ImGui::InputFloat("Var 1", &var1, 10.0f, 1000.0f);
    ImGui::InputFloat("Var 2", &var2, 10.0f, 1000.0f);
    ImGui::InputFloat("Var 3", &var3, 10.0f, 1000.0f);
    ImGui::InputFloat("Var 4", &var4, 10.0f, 1000.0f);
    ImGui::InputFloat("Var 5", &var5, 10.0f, 1000.0f);

    ImGui::Text("");

    // Display FPS
    ImGuiIO& io = ImGui::GetIO();
    float fps = io.Framerate;
    ImGui::Text("FPS: %.1f", fps);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}