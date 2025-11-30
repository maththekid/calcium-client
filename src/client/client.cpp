#include<chrono>
#include<iostream>
#include<thread>
#include<Windows.h>

#include<minhook/MinHook.h>

#include "./client.hpp"
#include "./hooks/hooks.hpp"
#include "./menu/menu.hpp"
#include "./module/moduleManager.hpp"
#include "sdk/sdk.hpp"
#include "./utils/requestUtils.hpp"

namespace Client
{
	static FILE* g_conout;
	static HINSTANCE g_instance = nullptr;

	static bool g_running = false;

	static std::vector<std::string> cache_names;

	void OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
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

		if(!Hooks::InitHooks())
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
				break;
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
		Hooks::ShutdownHooks();

		ModuleManager::Shutdown();
		
		SDK::Shutdown();

		fclose(Client::g_conout);
		FreeConsole();
		FreeLibraryAndExitThread(Client::g_instance, 0);
	}
}
