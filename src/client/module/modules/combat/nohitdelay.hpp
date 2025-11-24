#pragma once

#include "../../module.hpp"

class NoHitDelay : public Module
{
	public:
		NoHitDelay();

	private:
		void onEnable() override;
		void onDisable() override;
		void onRunning() override;
};
