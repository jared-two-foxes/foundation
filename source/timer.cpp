
#include <foundation/timer.hpp>
#include <foundation/timeHelpers.hpp>

#include <mutex>
#include <vector>


struct Timer 
{
  uuid id;
  time_t startAt;
  float delay;
  TimerType flag;
  std::function<void () > callback;
};

bool running;
std::mutex mutex;
std::vector<Timer > s_instances;

uuid AddTimer( float delay, TimerType flag, std::function<void () > callback ) 
{
  uuid id = getUuid();
  time_t now = Foundation::now();
  std::lock_guard<std::mutex> lock(mutex);
  s_instances.push_back( { id, now, delay, flag, callback } );
  //@todo: Sort list based upon expiry time.
  return id;
} 

void StopTimer( uuid handle ) 
{
  //@todo: do something!
}

void TimerThread() 
{  
  while ( running ) 
  {
    UpdateTimers();
  }
}

void UpdateTimers() 
{
  // Get the current time.
  time_t now = Foundation::now();

  // Iterate all the timers until you get one that will expire past the current
  // time 
  for ( Timer& t : s_instances ) 
  {
    float dt = Foundation::calcDiff( now, Foundation::addDelay( t.startAt, t.delay ) );
    if ( dt < 0 ) 
    {
      t.callback(); //< invoke callback.
    }
    else 
    {
      //@todo: add a delay?
      continue;
    }
  }

  //@todo: remove used timers.
}