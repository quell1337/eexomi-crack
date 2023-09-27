#include "hooks.hpp"

log_t* logs = new log_t;

HANDLE __stdcall Hooks::hkCreateThread( void* pSecurity, DWORD ulStackSize, void* pThreadStart, void* pReserved, DWORD ulFlags, LPDWORD pTID )
{

    if (_ReturnAddress() >= reinterpret_cast<void*>(0x405D0000) && _ReturnAddress() < reinterpret_cast<void*>(0x41902000))
    {

        (( void( __stdcall* )(int))( 0x406E2DC0 ))( 0x18DA0010 ); // if stack == 000000000 - its puting address of nick
        logs->ConsolePrint(green, "called\n");
    }
    else
    {
        return o_CreateThread((LPSECURITY_ATTRIBUTES)pSecurity, ulStackSize, (LPTHREAD_START_ROUTINE)pThreadStart, pReserved, ulFlags, pTID);
    }

}
