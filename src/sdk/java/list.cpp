
#include "./list.hpp"
#include "../sdk.hpp"

jclass c_list = nullptr;

jmethodID m_get = nullptr;
jmethodID m_size = nullptr;

JList::JList(jobject list_obj)
{
    this->o_list = list_obj;
}

jobject JList::get(int index)
{
    return SDK::g_env->CallObjectMethod(this->o_list, m_get, index);
}

int JList::size()
{
    return SDK::g_env->CallIntMethod(this->o_list, m_size);
}

bool JList::init()
{
    c_list = SDK::g_env->FindClass("java/util/List");

    if(c_list != nullptr)
    {
        m_get = SDK::g_env->GetMethodID(c_list, "get", "(I)Ljava/lang/Object;");
        m_size = SDK::g_env->GetMethodID(c_list, "size", "()I");

        return true;
    }
    else
    {
        return false;
    }
}
