#include <iostream>
#include <filesystem>

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <emscripten/emscripten.h>
#include <emscripten/em_js.h>

#include "window.hpp"

GLFWwindow* window;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
int g_width;
int g_height;

EM_JS(int, canvas_get_width, (), {
  return Module.canvas.width;
});

EM_JS(int, canvas_get_height, (), {
  return Module.canvas.height;
});

EM_JS(void, resizeCanvas, (), {
  js_resizeCanvas();
});

void on_size_changed() {
    glfwSetWindowSize(window, g_width, g_height);

    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
}

void loop() {
    const int width = canvas_get_width();
    const int height = canvas_get_height();

    if (width != g_width || height != g_height) {
        g_width = width;
        g_height = height;
        on_size_changed();
    }

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    createImGUIWindow();

    ImGui::Render();

    int display_w, display_h;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(window);
}

void initGL() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const int canvasWidth = g_width;
    const int canvasHeight = g_height;
    window = glfwCreateWindow(canvasWidth, canvasHeight, "Hello World", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
}

void initImGui() {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.Fonts->AddFontDefault();
    //const std::filesystem::path fontPath = ("assets" / "fonts" / "JetBrainsMono.ttf");
    //std::cout << fontPath << std::endl;
    //io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMono.ttf", 16.0f);
    ImGui::StyleColorsDark();

    resizeCanvas();
}

void init() {
    initGL();
    initImGui();
}

void quit() {
    glfwTerminate();
}

int main() {
    g_width = canvas_get_width();
    g_height = canvas_get_height();
    init();
    emscripten_set_main_loop(loop, 0, 1);
    quit();
    return 0;
}
