#include "./module.hpp"

Module::Module(std::string name, int keybind)
{
	this->name = name;
	this->keybind = keybind;
}

void Module::toggle()
{
	this->enabled = !this->enabled;

	if(this->enabled)
	{
		onEnable();
	}
	else
	{
		onDisable();
	}
}
