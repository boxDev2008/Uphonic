#pragma once
#include <cstdint>

enum class RendererType : uint8_t
{
    None = 0,
    D3D11,
    OPENGL
};

class Renderer
{
public:
    virtual ~Renderer(void) { }

    virtual void Begin(void) const = 0;
    virtual void End(void) const = 0;

    RendererType GetType(void) const { return m_type; }

protected:
    RendererType m_type;
};

Renderer *CreateRenderer(const RendererType type, void *window_handle);