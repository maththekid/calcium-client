#include<chrono>
#include<cstdio>
#include<iostream>
#include<thread>
#include<Windows.h>

#include<minhook/MinHook.h>
#include<imguihook/imgui_hook.h>

#include "./menu/menu.hpp"
#include "./client.hpp"

namespace Client
{
	static FILE* g_conout;
	static HINSTANCE g_instance = nullptr;

	static bool g_running = false;

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

		if(!ImGuiHook::Load(Menu::RenderMenu, Menu::OnWndProc))
		{
			Client::Shutdown();

			return;
		}

		Client::g_running = true;

		while(Client::g_running)
		{
			if(GetAsyncKeyState(VK_DELETE))
			{
				Client::g_running = false;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(0));
		}

		Client::Shutdown();
	}

	void Shutdown()
	{
		ImGuiHook::Unload();

		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);

		fclose(Client::g_conout);
		FreeConsole();
		FreeLibrary(Client::g_instance);
	}
}