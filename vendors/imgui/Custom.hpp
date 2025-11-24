#pragma once
#include "imgui.h"
#include <string>

struct prizuin {
    std::string name;
    bool ativado;
};


namespace Custom {
    bool KeyBind(const char* label, int* k);
    void TextColored(const ImVec4& color, const char* fmt, ...);
};
