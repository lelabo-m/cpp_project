#ifndef TIMECOUNTER_HH_
# define TIMECOUNTER_HH_

class TimeCounter
{
public:
  TimeCounter();
  ~TimeCounter();
  int	GetTime();
  int	GetRealTime();
  void	Pause();
private:
  int	_starttime;
  int	_pausetime;
  bool	_pause;
};

#endif /* !TIMECOUNTER_HH_ */

