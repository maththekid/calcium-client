#include<Windows.h>
#include<gl/GL.h>
#include<iostream>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_opengl2.h>
#include<imgui/imgui_impl_win32.h>
#include<minhook/MinHook.h>

#include "./hooks.hpp"
#include "../client.hpp"
#include "../menu/menu.hpp"

typedef BOOL(WINAPI* t_wglswapbuffers)(HDC hdc);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooks
{
	static HGLRC g_context = nullptr;
	static HWND g_hwnd = nullptr;
	static t_wglswapbuffers o_wglswapbuffers = nullptr;
    static WNDPROC o_wndproc = nullptr;

	static bool g_init = false;
	
	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);

		if(Client::OnWndProc(hwnd, msg, wparam, lparam))
		{
			return true;
		}

		return CallWindowProc(o_wndproc, hwnd, msg, wparam, lparam);
	}

	static BOOL OnSwapBuffers(HDC hdc)
	{
		Hooks::g_hwnd = WindowFromDC(hdc);
		HGLRC o_context = wglGetCurrentContext();

		if(!Hooks::g_init)
		{
			Hooks::g_context = wglCreateContext(hdc);

			wglMakeCurrent(hdc, g_context);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			GLint m_viewport[4];

			glGetIntegerv(GL_VIEWPORT, m_viewport);

			glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glClearColor(0, 0, 0, 0);

			ImGui::CreateContext();

			o_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Hooks::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::OnWndProc)));

			ImGui_ImplWin32_Init(Hooks::g_hwnd);
			ImGui_ImplOpenGL2_Init();

			g_init = true;
		}

		wglMakeCurrent(hdc, g_context);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		Menu::RenderMenu();

		ImGui::EndFrame();

		ImGui::Render();

		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		wglMakeCurrent(hdc, o_context);

		return o_wglswapbuffers(hdc);
	}

	bool InitHooks()
	{
		HMODULE h_opengl = GetModuleHandleA("opengl32.dll");

		if(h_opengl != nullptr)
		{
			void* p_wglswapbuffers = GetProcAddress(h_opengl, "wglSwapBuffers");
		
			if(MH_CreateHook(p_wglswapbuffers, reinterpret_cast<void*>(Hooks::OnSwapBuffers), reinterpret_cast<void**>(&Hooks::o_wglswapbuffers)) != MH_OK)
			{
				return false;
			}

			if(MH_EnableHook(p_wglswapbuffers) != MH_OK)
			{
				return false;
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	void ShutdownHooks()
	{
		MH_DisableHook(MH_ALL_HOOKS);

		SetWindowLongPtr(Hooks::g_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::o_wndproc));
		
		MH_RemoveHook(MH_ALL_HOOKS);
	}
}
