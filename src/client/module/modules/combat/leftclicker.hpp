#pragma once

#include "../../module.hpp"
#include "../../../utils/timerUtils.hpp"

class LeftClicker : public Module
{
    public:
        LeftClicker();

    private:
        TimerUtils timer = TimerUtils();

        void onRunning() override;
};
