#include<cpr/cpr.h>

#include "./requestUtils.hpp"

namespace RequestUtils
{
    rapidjson::Document getAsJson(std::string url)
    {
        rapidjson::Document document;

        cpr::AsyncResponse a_response = cpr::GetAsync(cpr::Url{url.c_str()});

        document.Parse(a_response.get().text.c_str());

        return document;
    }
}
