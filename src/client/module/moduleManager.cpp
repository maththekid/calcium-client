#include "./moduleManager.hpp"
#include "./modules/combat/nohitdelay.hpp"

namespace ModuleManager {
	static std::vector<std::shared_ptr<Module>> g_modules;

	void Init()
	{
		ModuleManager::g_modules.push_back(std::make_shared<NoHitDelay>());
	}

	void Shutdown()
	{
		for(auto& module : g_modules)
		{
			module.reset();
		}

		g_modules.clear();
	}

	std::vector<std::shared_ptr<Module>> getModules() {
		return ModuleManager::g_modules;
	}
}
