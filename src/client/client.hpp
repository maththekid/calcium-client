#pragma once

#include<Windows.h>

namespace Client
{
	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void Init(HINSTANCE instance);

	void Shutdown();
}
