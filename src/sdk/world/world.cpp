#include<iostream>

#include "../java/list.hpp"
#include "../sdk.hpp"
#include "./world.hpp"

jclass c_world = nullptr;

// fields
jfieldID f_playerEntities = nullptr;

World::World(jobject world_obj)
{
    this->o_world = world_obj;
}

std::vector<Entity> World::getPlayerList()
{
    JList playerList(SDK::g_env->GetObjectField(this->o_world, f_playerEntities));
    std::vector<Entity> entities;

    if(playerList.size() > 0)
    {
        for(int i = 0; i < playerList.size(); i++)
        {
            jobject o_entity = playerList.get(0);

            if(o_entity != nullptr)
            {
                entities.push_back(Entity(o_entity));
            }
        }
    }

    return entities;
}

bool World::isInWorld()
{
    return this->o_world != nullptr;
}

bool World::init()
{
    c_world = SDK::g_env->FindClass("adm");

    if(c_world != nullptr)
    {
        f_playerEntities = SDK::g_env->GetFieldID(c_world, "j", "Ljava/util/List;");

        return true;
    }
    else
    {
        return false;
    }
}
