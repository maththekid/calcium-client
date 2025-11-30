#pragma once

#include<string>

#include<rapidjson/document.h>

namespace RequestUtils
{
    rapidjson::Document getAsJson(std::string url);
}
