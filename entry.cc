#define _WINSOCK_DEPRECATED_NO_WARNINGS // ratio + don't care
#define _CRT_SECURE_NO_WARNINGS // ratio + don't care
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <intrin.h>
#include <wininet.h>
#include <filesystem>
#include <fstream>
#include <format>
#include <map>
#include <array>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "Ws2_32.lib")
#include "min_hook.hpp"
#include "hooks.hpp"
#include <string>
#include <stdexcept>
#include <thread>

log_t* logz = new log_t;

auto open_binary( std::string m_sSource, std::vector< std::uint8_t >& m_aData ) -> void
{
    std::ifstream m_strFile(m_sSource, std::ios::binary);
    m_strFile.unsetf(std::ios::skipws);
    m_strFile.seekg(0, std::ios::end);

    const auto m_iSize = m_strFile.tellg();

    m_strFile.seekg(0, std::ios::beg);
    m_aData.reserve(static_cast<uint32_t>(m_iSize));
    m_aData.insert(m_aData.begin(), std::istream_iterator< std::uint8_t >(m_strFile), std::istream_iterator< std::uint8_t >());
    m_strFile.close();
}


auto imp_handling(  ) -> void
{

    *reinterpret_cast<FARPROC*>(0x41546000) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetStdHandle");
    *reinterpret_cast<FARPROC*>(0x41546008) = GetProcAddress(LoadLibraryA("USER32.dll"), "GetClipboardData");
    *reinterpret_cast<FARPROC*>(0x41546010) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "CryptGenRandom");
    *reinterpret_cast<FARPROC*>(0x41546018) = GetProcAddress(LoadLibraryA("SHELL32.dll"), "ILFree");
    *reinterpret_cast<FARPROC*>(0x41546020) = GetProcAddress(LoadLibraryA("WININET.dll"), "HttpOpenRequestA");
    *reinterpret_cast<FARPROC*>(0x41546028) = GetProcAddress(LoadLibraryA("SHLWAPI.dll"), "PathFileExistsA");
    *reinterpret_cast<FARPROC*>(0x41546030) = GetProcAddress(LoadLibraryA("d3dx9_43.dll"), "D3DXCreateTextureFromFileInMemoryEx");
    *reinterpret_cast<FARPROC*>(0x41546038) = GetProcAddress(LoadLibraryA("WTSAPI32.dll"), "WTSSendMessageW");
    *reinterpret_cast<FARPROC*>(0x41546040) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetCurrentProcess");
    *reinterpret_cast<FARPROC*>(0x41546048) = GetProcAddress(LoadLibraryA("USER32.dll"), "CharUpperBuffW");
    *reinterpret_cast<FARPROC*>(0x41546050) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "RegQueryValueExA");
    *reinterpret_cast<FARPROC*>(0x41546058) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "LocalAlloc");
    *reinterpret_cast<FARPROC*>(0x4154605C) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetCurrentProcess");
    *reinterpret_cast<FARPROC*>(0x41546060) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetCurrentThread");
    *reinterpret_cast<FARPROC*>(0x41546064) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "LocalFree");
    *reinterpret_cast<FARPROC*>(0x41546068) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetModuleFileNameW");
    *reinterpret_cast<FARPROC*>(0x4154606C) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetProcessAffinityMask");
    *reinterpret_cast<FARPROC*>(0x41546070) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "SetProcessAffinityMask");
    *reinterpret_cast<FARPROC*>(0x41546074) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "SetThreadAffinityMask");
    *reinterpret_cast<FARPROC*>(0x41546078) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "Sleep");
    *reinterpret_cast<FARPROC*>(0x4154607C) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "ExitProcess");
    *reinterpret_cast<FARPROC*>(0x41546080) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetLastError");
    *reinterpret_cast<FARPROC*>(0x41546084) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "FreeLibrary");
    *reinterpret_cast<FARPROC*>(0x41546088) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "LoadLibraryA");
    *reinterpret_cast<FARPROC*>(0x4154608C) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetModuleHandleA");
    *reinterpret_cast<FARPROC*>(0x41546090) = GetProcAddress(LoadLibraryA("KERNEL32.dll"), "GetProcAddress");
    *reinterpret_cast<FARPROC*>(0x41546098) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "OpenSCManagerW");
    *reinterpret_cast<FARPROC*>(0x4154609C) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "EnumServicesStatusExW");
    *reinterpret_cast<FARPROC*>(0x415460A0) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "OpenServiceW");
    *reinterpret_cast<FARPROC*>(0x415460A4) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "QueryServiceConfigW");
    *reinterpret_cast<FARPROC*>(0x415460A8) = GetProcAddress(LoadLibraryA("ADVAPI32.dll"), "CloseServiceHandle");
}

auto oep_eexomi(  ) -> void
{
    _asm
    {
        push 0x18DA0000 // push nickname adr
        push 1 
        push 0x405D0000 // push base address of cheat
        mov eax, 0x4155E6DB // mov eax, ep
        call eax // call eax ( ep )
    }
}

auto main(  ) -> void
{
    static Color gr = { 255,165,0,255 };
    static Color red = { 255,0,0,255 };
    std::vector< uint8_t > aBinary = { };
    std::vector< uint8_t > aNickname = { };
    open_binary( "C:\\405D0000.bin", aBinary );
    open_binary( "C:\\18DA0000.bin", aNickname );


    //ConMsg ConsolePrint = (ConMsg)GetProcAddress(GetModuleHandle("tier0.dll"), "?ConColorMsg@@YAXABVColor@@PBDZZ");

    logz->ConsolePrint(gr, "[ + ] binary inited\n");

    MEMORY_BASIC_INFORMATION mem;

    if (!VirtualQuery( reinterpret_cast<void*>( 0x405D0000 ), &mem, sizeof( mem ) ))
        return;


    memcpy(reinterpret_cast<void*>(0x405D0000), aBinary.data( ), aBinary.size( )); // segment cheat
    memcpy(reinterpret_cast<void*>(0x18DA0000), aNickname.data( ), aNickname.size( )); // name in menu

    logz->ConsolePrint(gr, "[ + ] segment copied\n");

    while (!GetModuleHandleA( "serverbrowser.dll" ) )
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    imp_handling(  );

    logz->ConsolePrint(gr, "[ + ] imports handled\n");

    if ( MH_Initialize( ) != MH_OK )
    {
        logz->ConsolePrint(red, "[ ! ] protect not abused(((\n");
        return;
    }

    if ( MH_CreateHookApi(L"KERNEL32.dll", "CreateThread", Hooks::hkCreateThread, (LPVOID*)&Hooks::o_CreateThread) != MH_OK ) // $$$ fucked vmp $$$
    {
        logz->ConsolePrint( red, "[ ! ] protect not abused(((\n" );
        return;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        logz->ConsolePrint(red, "[ ! ] protect not abused(((\n");
        return;
    }

    logz->ConsolePrint(gr, "[ + ] p100 protect abused\n");


    HANDLE hThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(oep_eexomi), 0, 0, 0); // call ep

    logz->ConsolePrint(gr, "[ + ] done\n");
    logz->ConsolePrint(gr, "[ + ] vmp abusers cracked again?\n");
    logz->ConsolePrint(red, "[ =) ] haters where are you now??????????????\n");


}

bool __stdcall DllMain(HANDLE hinstDLL, uint32_t fdwReason, void* lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        /*AllocConsole();
        freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
        freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
        SetConsoleTitleA("t.me/chzxreverse");*/
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), 0, 0, 0);

    }
    return true;
}
