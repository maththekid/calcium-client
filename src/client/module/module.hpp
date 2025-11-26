#pragma once

#include<string>

class Module
{
	public:
		std::string name;
		int keybind = 0;
		bool enabled = false;

		Module(std::string name, int keybind);

		void toggle();
		
		virtual void onRunning() {}
		virtual void renderSetting() {}
	protected:
		virtual void onEnable() {}
		virtual void onDisable() {}
};
