#pragma once

#include<jni/jni.h>

class Minecraft
{
	private:
		jobject o_minecraft = nullptr;

		Minecraft(jobject minecraft_obj);

	public:
		void setLeftClickCounter(int counter);

		static Minecraft getMinecraft();
		static int getFps();

		static bool init();
};
