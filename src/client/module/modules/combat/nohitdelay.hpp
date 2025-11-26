#pragma once

#include "../../module.hpp"

class NoHitDelay : public Module
{
	public:
		NoHitDelay();

		void onRunning() override;
		void renderSetting() override;
	private:
		int counter;
};
