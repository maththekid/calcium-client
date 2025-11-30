#include "./timerUtils.hpp"

TimerUtils::TimerUtils()
{
    this->last_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch()).count();
}

bool TimerUtils::isTimerPassed(long ms, bool resetAfter)
{
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch()).count() - this->last_ms >= ms)
    {
        if(resetAfter)
        {
            this->last_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock().now().time_since_epoch()).count();
        }

        return true;
    }
    else
    {
        return false;
    }
}
