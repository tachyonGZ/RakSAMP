/*
	Updated to 0.3.7 by P3ti
*/
#pragma once

extern HWND hwnd, texthwnd, loghwnd, inputhwnd;
extern HINSTANCE g_hInst;

void SetUpWindow(HINSTANCE hInstance, std::unique_ptr<std::thread> &);

LRESULT CALLBACK TeleportMenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI TeleportMenuThread(PVOID);