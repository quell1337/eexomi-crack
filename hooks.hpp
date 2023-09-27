#include <Windows.h>
#include <iostream>
#include <WinInet.h>
#include <intrin.h>

struct Color
{
    byte r, g, b, a;
};


static Color green = { 0,255,0,255 };
typedef void(__cdecl* ColorMsgFn)(Color& color, const char* msg, ...);
class log_t
{
public:
    ColorMsgFn ConsolePrint = (ColorMsgFn)GetProcAddress(GetModuleHandle("tier0.dll"), "?ConColorMsg@@YAXABVColor@@PBDZZ");
};

namespace Hooks
{
    typedef HANDLE(__stdcall* CreateThread_t)(void*, DWORD, void*, void*, DWORD, LPDWORD);
    inline CreateThread_t o_CreateThread = nullptr; // original

    HANDLE __stdcall hkCreateThread(void* pSecurity, DWORD ulStackSize, void* pThreadStart, void* pReserved, DWORD ulFlags, LPDWORD pTID);

}
