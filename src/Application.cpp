#include "Application.h"
#include "imgui.h"

Application::Application(void)
{   
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    m_mainWindow = CreatePlatformWindow();
    m_renderer = CreateRenderer(RendererType::D3D11, m_mainWindow->GetHandle());

    while (m_mainWindow->IsRunning())
    {
        m_mainWindow->PollEvents();
        m_renderer->Begin();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        m_renderer->End();
    }
}

Application::~Application(void)
{
    delete m_renderer;
    delete m_mainWindow;
    ImGui::DestroyContext();
}