#pragma once

#include<Windows.h>

namespace Client
{
	inline HWND g_hwnd = nullptr;

	void OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Init(HINSTANCE instance);

	void Shutdown();
}
