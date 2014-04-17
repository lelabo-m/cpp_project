#include <iostream>
#include <cstdlib>
#include <sys/timeb.h>
#include "timecounter.hh"

TimeCounter::TimeCounter()
{
  _starttime = GetRealTime();
  _pausetime = 0;
  _pause = false;
}

TimeCounter::~TimeCounter()
{

}

int TimeCounter::GetRealTime()
{
  timeb timedata;

  ftime(&timedata);
  int  t = timedata.millitm + (timedata.time & 0xfffff) * 1000;
  return t;
}

int TimeCounter::GetTime()
{
  int n = GetRealTime() - _starttime;
  if(n < 0)
    n += 0x100000 * 1000;
  return n;
}

void	TimeCounter::Pause()
{
  if (_pause == true)
    {
      int	pausedelay;

      pausedelay = (GetRealTime() - _starttime) - _pausetime;
      _starttime += pausedelay;
      _pause = false;
    }
  else
    {
      _pausetime = GetRealTime() - _starttime;
      _pause = true;
    }
}
