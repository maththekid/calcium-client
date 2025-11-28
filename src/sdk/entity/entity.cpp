#include "./entity.hpp"
#include "../sdk.hpp"

jclass c_entity = nullptr;

jmethodID m_getName = nullptr;

Entity::Entity(jobject entity_obj)
{
    this->o_entity = entity_obj;
}

std::string Entity::getName()
{
    jstring t_string = reinterpret_cast<jstring>(SDK::g_env->CallObjectMethod(this->o_entity, m_getName));
    const char* a_string = SDK::g_env->GetStringUTFChars(t_string, nullptr);
    std::string name = a_string;

    SDK::g_env->ReleaseStringUTFChars(t_string, a_string);

    return name;
}

bool Entity::init()
{
    c_entity = SDK::g_env->FindClass("pk");

    if(c_entity != nullptr)
    {
        m_getName = SDK::g_env->GetMethodID(c_entity, "e_", "()Ljava/lang/String;");

        return true;
    }
    else
    {
        return false;
    }
}
