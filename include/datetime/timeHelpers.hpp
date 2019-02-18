#ifndef FOUNDATION_TIMEHELPERS_HPP__
#define FOUNDATION_TIMEHELPERS_HPP__

#include <time.h>

namespace Foundation 
{

time_t now();

float calcDiff( time_t b, time_t a);
time_t addDelay( time_t start, float delay );

}

#endif // FOUNDATION_TIME_HPP__