#include<Windows.h>

#include "../../../client.hpp"
#include "./leftclicker.hpp"

LeftClicker::LeftClicker() : Module("LeftClicker", 0)
{
}

void LeftClicker::onRunning()
{
    if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        if(this->timer.isTimerPassed(83, false))
        {
            POINT p_mouse;

            GetCursorPos(&p_mouse);

            SendMessage(Client::g_hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(p_mouse.x, p_mouse.y));
            SendMessage(Client::g_hwnd, WM_LBUTTONUP, 0, MAKELPARAM(p_mouse.x, p_mouse.y));
        }
    }
}
