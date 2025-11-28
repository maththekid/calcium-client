#pragma once

#include<string>

#include<jni/jni.h>

class Entity
{
    private:
        jobject o_entity = nullptr;
    
    public:
        Entity(jobject entity_obj);

        std::string getName();

        static bool init();
};
