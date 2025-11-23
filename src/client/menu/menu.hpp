#pragma once

#include<Windows.h>

namespace Menu
{
	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM param);

	void RenderMenu();
}
