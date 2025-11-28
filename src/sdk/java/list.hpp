#pragma once

#include<jni/jni.h>

class JList
{
    private:
        jobject o_list;
    
    public:
        JList(jobject list_obj);

        jobject get(int index);
        int size();

        static bool init();
};
