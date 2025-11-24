#pragma

#include<memory>
#include<vector>

#include "./module.hpp"

namespace ModuleManager
{
	void Init();

	void Shutdown();

	std::vector<std::shared_ptr<Module>> getModules();
};
