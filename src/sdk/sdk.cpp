#include "./client/minecraft.hpp"
#include "./sdk.hpp"

namespace SDK {
	bool Init()
	{
		JNI_GetCreatedJavaVMs(&SDK::g_jvm, 1, nullptr);

		if(SDK::g_jvm == nullptr)
		{
			return false;
		}

		if(SDK::g_jvm->GetEnv(reinterpret_cast<void**>(&SDK::g_env), JNI_VERSION_1_6) == JNI_EDETACHED)
		{
			SDK::g_jvm->AttachCurrentThread(reinterpret_cast<void**>(&SDK::g_env), nullptr);
		}

		if(!Minecraft::init())
		{
			return false;
		}

		return true;
	}

	void Shutdown()
	{
		if(SDK::g_jvm != nullptr)
		{
			SDK::g_jvm->DetachCurrentThread();
		}
	}
}