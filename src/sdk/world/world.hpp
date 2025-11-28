#pragma once

#include<vector>

#include<jni/jni.h>

#include "../entity/entity.hpp"

class World
{
    private:
        jobject o_world = nullptr;

    public:
        World(jobject world_obj);

        std::vector<Entity> getPlayerList();
        bool isInWorld();

        static bool init();
};
