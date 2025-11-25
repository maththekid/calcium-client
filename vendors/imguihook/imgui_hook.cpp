#include "imgui_hook.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>

#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND hWnd, 
    UINT msg, 
    WPARAM wParam, 
    LPARAM lParam);

namespace ImGuiHook 
{
    typedef BOOL(__stdcall* wglSwapBuffers_t) (HDC hDc);

    typedef LRESULT(CALLBACK* WNDPROC) (
        IN  HWND   hwnd,
        IN  UINT   uMsg,
        IN  WPARAM wParam,
        IN  LPARAM lParam);

    // Original functions variables
    static WNDPROC          g_WndProc_o        = nullptr;
    static wglSwapBuffers_t g_wglSwapBuffers_o = nullptr;

    // Global variables
    static HGLRC g_wglContext = nullptr;
    static bool	 g_init       = false;
    static HWND  g_hWnd       = nullptr;

    // Render function variables
    static std::function<void()> g_renderMain = []() {};
    static std::function<void()> g_extraInit  = []() {};
    static std::function<bool(HWND, UINT, WPARAM, LPARAM)> g_wndprocfunction = [](HWND, UINT, WPARAM, LPARAM) {return false;};

    // Last error status
    static std::string g_lastError;

    // WndProc callback ImGui handler
    static LRESULT CALLBACK ImGui_WndProc(
        const HWND	hWnd, 
        UINT		uMsg, 
        WPARAM		wParam, 
        LPARAM		lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) || g_wndprocfunction(hWnd, uMsg, wParam, lParam))
            return true;

        return CallWindowProc(g_WndProc_o, hWnd, uMsg, wParam, lParam);
    }

    // Hooked wglSwapBuffers function
    static BOOL WINAPI wglSwapBuffers_h(const HDC hDc)
    {
        if(WindowFromDC(hDc) != g_hWnd)
        {
            g_hWnd = WindowFromDC(hDc);
        }

        if(!g_init)
        {
            g_WndProc_o = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)ImGui_WndProc);
            
            g_wglContext = wglCreateContext(hDc);

            ImGui::CreateContext();

            ImGui_ImplWin32_Init(g_hWnd);
            ImGui_ImplOpenGL2_Init();

            g_extraInit();

            g_init = true;
        }

        HGLRC o_WglContext = wglGetCurrentContext();

        wglMakeCurrent(hDc, g_wglContext);

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        g_renderMain();

        ImGui::EndFrame();
        ImGui::Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        wglMakeCurrent(hDc, o_WglContext);

        return g_wglSwapBuffers_o(hDc);
    }

    // Initialise hook
    static bool InitHook()
    {
        if (auto hMod = GetModuleHandleA("OPENGL32.dll")) 
            g_wglSwapBuffers_o = (wglSwapBuffers_t)GetProcAddress(hMod, "wglSwapBuffers");
        
        const auto status = kiero::init(kiero::RenderType::OpenGL);

        if (g_wglSwapBuffers_o && status == kiero::Status::Success)
            return kiero::bind((void*) g_wglSwapBuffers_o, (void**)&g_wglSwapBuffers_o, (void*) wglSwapBuffers_h) == kiero::Status::Success;
        else
            g_lastError = "Failed to do kiero::init, error code: " + std::to_string(status);

        return false;
    }

    std::string GetLastError()
    {
        return g_lastError;
    }

    // Main load function
    bool Load(const std::function<void()>& render, const std::function<bool(HWND, UINT, WPARAM, LPARAM)>& wndproc, const std::function<void()>& init)
    {
        g_renderMain = render;
        g_wndprocfunction = wndproc;
        g_extraInit = init;
        return InitHook();
    }

    // Main unload function
    void Unload()
    {
        SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)g_WndProc_o);
        kiero::shutdown();
    }
}


