#include<Windows.h>

#include<imgui/imgui.h>

#include "./nohitdelay.hpp"
#include "sdk/client/minecraft.hpp"

NoHitDelay::NoHitDelay() : Module("No Hit Delay", VK_HOME)
{
}

void NoHitDelay::onRunning()
{
	Minecraft::getMinecraft().setLeftClickCounter(0);
}

void NoHitDelay::renderSetting()
{
	ImGui::SliderInt("##nohitdelaycounter", &this->counter, 0, 10, "Counter: %d");
}
