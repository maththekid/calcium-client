#pragma once

#include "../../module.hpp"

class NoHitDelay : public Module
{
	public:
		NoHitDelay();

	private:
		int counter;

		void onRunning() override;
		void renderSetting() override;
};
