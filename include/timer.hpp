#ifndef TIMER_HPP__
#define TIMER_HPP__

#include <foundation/uuid.hpp>

#include <functional>

enum class TimerType 
{
  ONE_SHOT, 
  CYCLE
};

uuid AddTimer( float delay, TimerType flag, std::function<void () > callback );
void StopTimer( uuid handle );

void UpdateTimers();

#endif // TIMER_HPP__