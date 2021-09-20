#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x401

#include <windows.h>
#include <winuser.h>

#include "WinKillExHook.h"

HHOOK hook = NULL;
HWND hwnd = NULL;
HINSTANCE instance = NULL;

BOOL APIENTRY DllMain(HANDLE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        ::instance = (HINSTANCE) module;
        break;

    case DLL_PROCESS_DETACH:
        WinKillEx_remove_hook();
        break;
    }

    return TRUE;
}

WinKillExHOOK_API LRESULT CALLBACK keyboard_proc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        switch (wParam) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP: {
                PKBDLLHOOKSTRUCT hook_struct = (PKBDLLHOOKSTRUCT)lParam;
                DWORD keyCode = hook_struct->vkCode;

                if ((keyCode == VK_LWIN) || (keyCode == VK_RWIN)) {
                    return 1;
                }
                if ((keyCode == VK_TAB && (hook_struct->flags && KF_ALTDOWN) != 0))
                {
                    return 1;
                }
                if ((keyCode == VK_TAB && (hook_struct->flags && KF_ALTDOWN) != 0))
                {
                    return 1;
                }
            }
            break;
        }
    }

    return ::CallNextHookEx(NULL, nCode, wParam, lParam);
}

WinKillExHOOK_API bool WinKillEx_install_hook(HWND owner) {
    if ((!::hook) && owner) {
        ::hwnd = owner;
        ::hook = ::SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_proc, instance, NULL);
    }

    return (::hook != NULL);
}

WinKillExHOOK_API bool WinKillEx_remove_hook() {
    if ((::hook) && (::UnhookWindowsHookEx(::hook))) {
        ::hook = NULL;
        ::hwnd = NULL;
    }

    return (::hook == NULL);
}
