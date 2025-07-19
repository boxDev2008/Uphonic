#pragma once

#include "Renderer.h"
#include "imgui_impl_dx11.h"

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

class D3D11Renderer : public Renderer
{
public:
    D3D11Renderer(void *window_handle);
    ~D3D11Renderer(void);

    void Begin(void) const override;
    void End(void) const override;

private:
    HWND                     m_hwnd = nullptr;
    ID3D11Device*            m_pd3dDevice = nullptr;
    ID3D11DeviceContext*     m_pd3dDeviceContext = nullptr;
    IDXGISwapChain*          m_pSwapChain = nullptr;
    UINT                     m_ResizeWidth = 0, m_ResizeHeight = 0;
    ID3D11RenderTargetView*  m_mainRenderTargetView = nullptr;

    bool CreateDeviceD3D(HWND hWnd);
    void CleanupDeviceD3D(void);
    void CreateRenderTarget(void);
    void CleanupRenderTarget(void);
};

D3D11Renderer::D3D11Renderer(void *window_handle)
{
    m_hwnd = (HWND)window_handle;
    if (!CreateDeviceD3D(m_hwnd))
    {
        CleanupDeviceD3D();
        return;
    }

    //CleanupRenderTarget();
    m_pSwapChain->ResizeBuffers(0, 1280, 800, DXGI_FORMAT_UNKNOWN, 0);
    //g_ResizeWidth = g_ResizeHeight = 0;
    CreateRenderTarget();

    ImGui_ImplDX11_Init(m_pd3dDevice, m_pd3dDeviceContext);
    m_type = RendererType::D3D11;
}

D3D11Renderer::~D3D11Renderer(void)
{
    ImGui_ImplDX11_Shutdown();
    CleanupDeviceD3D();
}

void D3D11Renderer::Begin(void) const
{
    ImGui_ImplDX11_NewFrame();
}

void D3D11Renderer::End(void) const
{
    const float clear_color_with_alpha[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_pd3dDeviceContext->OMSetRenderTargets(1, &m_mainRenderTargetView, nullptr);
    m_pd3dDeviceContext->ClearRenderTargetView(m_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    HRESULT hr = m_pSwapChain->Present(1, 0);
}

bool D3D11Renderer::CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &featureLevel, &m_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &featureLevel, &m_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void D3D11Renderer::CleanupDeviceD3D(void)
{
    CleanupRenderTarget();
    if (m_pSwapChain) { m_pSwapChain->Release(); m_pSwapChain = nullptr; }
    if (m_pd3dDeviceContext) { m_pd3dDeviceContext->Release(); m_pd3dDeviceContext = nullptr; }
    if (m_pd3dDevice) { m_pd3dDevice->Release(); m_pd3dDevice = nullptr; }
}

void D3D11Renderer::CreateRenderTarget(void)
{
    ID3D11Texture2D* pBackBuffer;
    m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_mainRenderTargetView);
    pBackBuffer->Release();
}

void D3D11Renderer::CleanupRenderTarget(void)
{
    if (m_mainRenderTargetView) { m_mainRenderTargetView->Release(); m_mainRenderTargetView = nullptr; }
}