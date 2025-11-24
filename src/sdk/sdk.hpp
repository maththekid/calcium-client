#pragma once

#include<jni/jni.h>

namespace SDK
{
	inline JNIEnv* g_env = nullptr;
	inline JavaVM* g_jvm = nullptr;

	bool Init();

	void Shutdown();
}
