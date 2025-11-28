#include "./minecraft.hpp"
#include "../sdk.hpp"

static jclass c_minecraft = nullptr;

// fields
static jfieldID f_debugFPS = nullptr;
static jfieldID f_leftClickCounter = nullptr;
static jfieldID f_theMinecraft = nullptr;
static jfieldID f_theWorld = nullptr;

Minecraft::Minecraft(jobject minecraft_obj)
{
	this->o_minecraft = minecraft_obj;
}

void Minecraft::setLeftClickCounter(int counter)
{
	SDK::g_env->SetIntField(this->o_minecraft, f_leftClickCounter, counter);
}

Minecraft Minecraft::getMinecraft()
{
	return Minecraft(SDK::g_env->GetStaticObjectField(c_minecraft, f_theMinecraft));
}

World Minecraft::getLocalWorld()
{
	return World(SDK::g_env->GetObjectField(this->o_minecraft, f_theWorld));
}

bool Minecraft::init()
{
	c_minecraft = SDK::g_env->FindClass("ave");

	if(c_minecraft != nullptr)
	{
		f_debugFPS = SDK::g_env->GetStaticFieldID(c_minecraft, "ao", "I");
		f_leftClickCounter = SDK::g_env->GetFieldID(c_minecraft, "ag", "I");
		f_theMinecraft = SDK::g_env->GetStaticFieldID(c_minecraft, "S", "Lave;");
		f_theWorld = SDK::g_env->GetFieldID(c_minecraft, "f", "Lbdb;");

		return true;
	}
	else
	{
		return false;
	}
}

int Minecraft::getFps()
{
	return SDK::g_env->GetStaticIntField(c_minecraft, f_debugFPS);
}
