#pragma once

#include<chrono>

class TimerUtils
{
    public:
        TimerUtils();

        bool isTimerPassed(long ms, bool resetAfter);
    private:
        long long last_ms;
};
