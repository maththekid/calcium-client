#include<chrono>
#include<iostream>
#include<thread>
#include<Windows.h>

#include<minhook/MinHook.h>
#include<imguihook/imgui_hook.h>

#include "./client.hpp"
#include "./menu/menu.hpp"
#include "./module/moduleManager.hpp"
#include "sdk/sdk.hpp"

namespace Client
{
	static FILE* g_conout;
	static HINSTANCE g_instance = nullptr;

	static bool g_running = false;

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM param)
	{
		if(msg == WM_KEYUP)
		{
			if(wparam == VK_INSERT)
			{
				Menu::g_opened = !Menu::g_opened;
			}
			
			for(auto& module : ModuleManager::GetModules())
			{
				if(wparam == module->keybind)
				{
					module->toggle();
				}
			}
		}

		return Menu::g_opened;
	}

	void Init(HINSTANCE instance)
	{
		Client::g_instance = instance;

		std::ios::sync_with_stdio(false);

		AllocConsole();
		freopen_s(&Client::g_conout, "CONOUT$", "w", stdout);

		if(MH_Initialize() != MH_OK)
		{
			Client::Shutdown();
			
			return;
		}

		if(!SDK::Init())
		{
			Client::Shutdown();

			return;
		}

		if(!ImGuiHook::Load(Menu::RenderMenu, Client::OnWndProc))
		{
			Client::Shutdown();

			return;
		}

		ModuleManager::Init();

		Client::g_running = true;

		while(Client::g_running)
		{
			if(GetAsyncKeyState(VK_DELETE))
			{
				Client::g_running = false;
			}

			for(auto& module : ModuleManager::GetModules())
			{
				if(module->enabled)
				{
					module->onRunning();
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(0));
		}

		Client::Shutdown();
	}

	void Shutdown()
	{
		SDK::Shutdown();

		MH_DisableHook(MH_ALL_HOOKS);

		ImGuiHook::Unload();

		ModuleManager::Shutdown();

		MH_RemoveHook(MH_ALL_HOOKS);

		fclose(Client::g_conout);
		FreeConsole();
		FreeLibraryAndExitThread(Client::g_instance, 0);
	}
}
