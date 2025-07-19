#include "Renderer.h"
#include "Base.h"

#if UPHONIC_PLATFORM_WINDOWS
#include "D3D11Renderer.h"
#endif

Renderer *CreateRenderer(const RendererType type, void *window_handle)
{
    switch (type)
    {
#if UPHONIC_PLATFORM_WINDOWS
    case RendererType::D3D11:
        return new D3D11Renderer(window_handle);
#endif
    default:
        return nullptr;
    }
}