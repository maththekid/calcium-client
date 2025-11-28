#pragma once

#include<jni/jni.h>

#include "../world/world.hpp"

class Minecraft
{
	private:
		jobject o_minecraft = nullptr;

		Minecraft(jobject minecraft_obj);

	public:
		void setLeftClickCounter(int counter);

		static Minecraft getMinecraft();
		World getLocalWorld();
		static int getFps();

		static bool init();
};
