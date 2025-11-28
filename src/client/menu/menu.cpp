#include<format>

#include<imgui/Custom.hpp>
#include<imgui/imgui.h>
#include<imgui/imgui_internal.h>

#include "../module/moduleManager.hpp"
#include "./menu.hpp"
#include "sdk/client/minecraft.hpp"
#include "sdk/entity/entity.hpp"

namespace Menu
{
	void RenderMenu()
	{
		if(Menu::g_opened)
		{
			ImGui::Begin("Penis");

			for(auto& module : ModuleManager::GetModules())
			{
				bool tmp_enabled = module->enabled;

				if(ImGui::Checkbox(std::format("Toggle {}", module->name).c_str(), &tmp_enabled))
				{
					module->toggle();
				}

				if(tmp_enabled)
				{
					module->renderSetting();
				}
			}

			ImGui::End();
		}
	}
}
