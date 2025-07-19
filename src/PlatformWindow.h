#pragma once

class PlatformWindow
{
public:
    virtual ~PlatformWindow(void) { }

    virtual bool IsRunning(void) const = 0;
    virtual void *GetHandle(void) const = 0;

    virtual void PollEvents(void) = 0;
};

PlatformWindow *CreatePlatformWindow(void);