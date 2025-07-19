#include "PlatformWindow.h"

#include "imgui.h"
#include "imgui_impl_win32.h"

#include <windows.h>

class Win32Window : public PlatformWindow
{
public:
    Win32Window(void);
    ~Win32Window(void);

    bool IsRunning(void) const override { return m_isRunning;}
    void *GetHandle(void) const override { return m_hwnd; }

    void PollEvents(void) override;

private:
    HWND m_hwnd = nullptr;
    HINSTANCE m_hInstance = nullptr;

    bool m_isRunning = false;
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        //g_ResizeWidth = (UINT)LOWORD(lParam);
        //g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

Win32Window::Win32Window(void)
{
    m_hInstance = GetModuleHandle(nullptr);
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, m_hInstance, nullptr, LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, L"uphonic_window_class", nullptr };
    ::RegisterClassExW(&wc);
    m_hwnd = ::CreateWindowW(wc.lpszClassName, L"Uphonic", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    ::ShowWindow(m_hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(m_hwnd);

    ImGui_ImplWin32_Init(m_hwnd);

    m_isRunning = true;
}

Win32Window::~Win32Window(void)
{
    ImGui_ImplWin32_Shutdown();
    DestroyWindow(m_hwnd);
    UnregisterClassW(L"uphonic_window_class", m_hInstance);
}

void Win32Window::PollEvents(void)
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            m_isRunning = false;
    }
    ImGui_ImplWin32_NewFrame();
}