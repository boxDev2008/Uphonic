#pragma once

#include "PlatformWindow.h"
#include "Renderer.h"

class Application
{
public:
    Application(void);
    ~Application(void);

private:
    PlatformWindow *m_mainWindow = nullptr;
    Renderer *m_renderer = nullptr;
};