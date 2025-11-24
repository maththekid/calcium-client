#include<iostream>
#include<Windows.h>

#include "./nohitdelay.hpp"
#include "sdk/client/minecraft.hpp"

NoHitDelay::NoHitDelay() : Module("No Hit Delay", VK_HOME)
{
}

void NoHitDelay::onEnable()
{
	std::cout << "ligado" << '\n';
}

void NoHitDelay::onDisable()
{
	std::cout << "desligado" << '\n';
}

void NoHitDelay::onRunning()
{
	Minecraft::getMinecraft().setLeftClickCounter(0);
}
