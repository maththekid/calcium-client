#include<imgui/Custom.hpp>
#include<imgui/imgui.h>
#include<imgui/imgui_internal.h>

#include "./menu.hpp"

namespace Menu
{
	void RenderMenu()
	{
		static int keytest = 0;

		if(Menu::g_opened)
		{
			ImGui::Begin("Roberto");

			ImGui::End();
		}
	}
}
