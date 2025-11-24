#include "imgui_internal.h"
#include <map>
#include "imgui_internal.h"
#include <windows.h>
#include <shobjidl.h>

#include "Custom.hpp"

void Custom::TextColored(const ImVec4& color, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextColoredV(color, fmt, args);
    va_end(args);
}


const char* const KeyNames[] = {
    "None",
    "Left Button",
    "Right Button",
    "Cancel",
    "Mouse Button",
    "Mouse 5",
    "Mouse 6",
    "Unknown",
    "Backspace",
    "TAB",
    "Unknown",
    "Unknown",
    "Clear",
    "Enter",
    "Unknown",
    "Unknown",
    "Shift",
    "Control",
    "ALT",
    "Pause",
    "Capital",
    "Kana",
    "Unknown",
    "Junja",
    "Final",
    "Kanji",
    "Unknown",
    "Escape",
    "Convert",
    "Nonconvert",
    "Accpet",
    "Mode Changer",
    "Space",
    "Prior",
    "Next",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "Select",
    "Print",
    "Execute",
    "Snapshot",
    "Insert",
    "Delete",
    "Help",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "Left Winndows",
    "Right Windows",
    "Apps",
    "Unknown",
    "Sleep",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "Multiply",
    "Add",
    "Separator",
    "Subtract",
    "Decimal",
    "Divided",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "VK_NUMLOCK",
    "VK_SCROLL",
    "VK_OEM_NEC_EQUAL",
    "VK_OEM_FJ_MASSHOU",
    "VK_OEM_FJ_TOUROKU",
    "VK_OEM_FJ_LOYA",
    "VK_OEM_FJ_ROYA",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "Unknown",
    "VK_LSHIFT",
    "VK_RSHIFT",
    "VK_LCONTROL",
    "VK_RCONTROL",
    "Left Menu",
    "Right Menu"
};

struct pumfedido2
{
    ImVec4 a;
    ImVec4 b;
    float c;
};

bool Custom::KeyBind(const char* label, int* k)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    const ImGuiStyle& style = g.Style;


    const ImGuiID id = window->GetID(label);

    static std::map<ImGuiID, pumfedido2> anim;
    auto it_anim = anim.find(id);

    if (it_anim == anim.end())
    {
        anim.insert({ id, pumfedido2() });
        it_anim = anim.find(id);
    }

    it_anim->second.c = ImLerp(it_anim->second.c, *k ? 1.f : 0.f, g.IO.DeltaTime * 10.f);

    float size = (ImGui::CalcTextSize(KeyNames[*k]).x + 10) * it_anim->second.c;

    if (g.ActiveId == id || *k == 0)
        size = 40;


    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    const ImRect frame_bb(window->DC.CursorPos + ImVec2(window->Size.x - 20 - size, 0), window->DC.CursorPos + ImVec2(window->Size.x - 20, 23));
    const ImRect total_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(window->Size.x - 40, 23));

    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;


    const bool hovered = ImGui::ItemHoverable(frame_bb, id, ImGuiWindowFlags_None);
    if (hovered) {
        ImGui::SetHoveredID(id);
        g.MouseCursor = ImGuiMouseCursor_TextInput;
    }


    char buf_display[64] = "None";
    if (*k != 0 && g.ActiveId != id)
    {
        strcpy_s(buf_display, sizeof(buf_display), KeyNames[*k]);
    }
    else if (g.ActiveId == id)
    {
        strcpy_s(buf_display, sizeof(buf_display), "Press");
    }

    char* output = strstr(buf_display, "None");
    char* output2 = strstr(buf_display, "Press");

    it_anim->second.a = ImLerp(it_anim->second.a, (output || output2) ? ImColor(186, 186, 186) : ImColor(255, 255, 255), g.IO.DeltaTime * 10.f);
    it_anim->second.b = ImLerp(it_anim->second.b, hovered ? ImColor(232, 63, 212, 50).Value : ImColor(ImGui::GetColorU32(ImGuiCol_Border)).Value, g.IO.DeltaTime * 10.f);

    window->DrawList->AddText(ImVec2(total_bb.Min.x + 15, frame_bb.Min.y + frame_bb.GetHeight() / 2 - ImGui::CalcTextSize(label).y / 2), ImColor(80, 80, 80), label);

    window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max, ImColor(14, 14, 14), 5);
    window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(it_anim->second.b), 5);
    ImGui::PushClipRect(frame_bb.Min, frame_bb.Max, true);
    window->DrawList->AddText(ImVec2(frame_bb.Min.x + 4, frame_bb.Min.y + frame_bb.GetHeight() / 2 - ImGui::CalcTextSize(label).y / 2), ImGui::GetColorU32(it_anim->second.a), buf_display);
    ImGui::PopClipRect();

    const bool user_clicked = hovered && io.MouseClicked[0];

    if (user_clicked)
    {
        if (g.ActiveId != id)
        {
            io.ClearInputKeys();
            io.ClearInputMouse();
            *k = 0;
        }
        ImGui::SetActiveID(id, window);
        ImGui::FocusWindow(window);
    }
    else if (io.MouseClicked[0])
    {
        if (g.ActiveId == id)
            ImGui::ClearActiveID();
    }


    bool value_changed = false;
    int key = *k;

    if (g.ActiveId == id)
    {
        for (auto i = 0; i < 5; i++)
        {
            if (io.MouseDown[i])
            {
                switch (i) {
                case 0:
                    key = VK_LBUTTON;
                    break;
                case 1:
                    key = VK_RBUTTON;
                    break;
                case 2:
                    key = VK_MBUTTON;
                    break;
                case 3:
                    key = VK_XBUTTON1;
                    break;
                case 4:
                    key = VK_XBUTTON2;
                    break;
                }
                value_changed = true;
                ImGui::ClearActiveID();
            }
        }
        if (!value_changed)
        {
            for (auto i = VK_BACK; i <= VK_RMENU; i++)
            {
                if (GetAsyncKeyState(i) & 0x8000)
                {
                    key = i;
                    value_changed = true;
                    ImGui::ClearActiveID();
                }
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey_End))
        {
            *k = 0;
            ImGui::ClearActiveID();
        }
        else
        {
            *k = key;
        }
    }

    return value_changed;
}