#include "PlatformWindow.h"
#include "Base.h"

#if UPHONIC_PLATFORM_WINDOWS
#include "Win32Window.h"
#endif

PlatformWindow *CreatePlatformWindow(void)
{
#if UPHONIC_PLATFORM_WINDOWS
    return new Win32Window;
#else
    return nullptr;
#endif
}