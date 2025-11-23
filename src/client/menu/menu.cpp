#include<imgui/imgui.h>
#include<imgui/imgui_internal.h>

#include "./menu.hpp"

namespace Menu
{
	static bool opened = false;

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM param)
	{
		if(msg == WM_KEYUP)
		{
			if(wparam == VK_INSERT)
			{
				Menu::opened = !Menu::opened;
			}
		}

		return opened;
	}

	void RenderMenu()
	{
		if(opened)
		{
			ImGui::Begin("fodase");
			ImGui::End();
		}
	}
}
