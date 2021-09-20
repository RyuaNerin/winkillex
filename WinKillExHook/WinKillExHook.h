#pragma once

#ifdef WinKillExHOOK_EXPORTS
#define WinKillExHOOK_API __declspec(dllexport)
#else
#define WinKillExHOOK_API __declspec(dllimport)
#endif

WinKillExHOOK_API bool WinKillEx_install_hook(HWND);
WinKillExHOOK_API bool WinKillEx_remove_hook();
