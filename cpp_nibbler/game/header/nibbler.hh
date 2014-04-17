#ifndef NIBBLER_HH_
# define NIBBLER_HH_

#include <string>
#include <list>
#include "timecounter.hh"
#include "graphics.hh"
#include "loader.hpp"
#include "snake.hh"
#include "map.hh"

namespace SnakeGame
{
  class EventManager;

  struct GameData
  {
    unsigned int	_incfood;
    unsigned int	_food;
    bool		_end;
    bool		_pause;
    unsigned int	_apples;
    unsigned int	_score;
    Map			*_map;
    Snake		*_player;
    std::list<Snake *>	_ialist;
  };

  class Nibbler
  {
  public:
    Nibbler(const std::string&, const std::string&);
    Nibbler(const std::string&, unsigned int, unsigned int, unsigned int);
    ~Nibbler();
    void	Init(const std::string&);
    void	InitEventManager();
    void	Launch();
    bool	GetIA() const;
    void	SetIA(bool);
    bool	GetER() const;
    void	SetER(bool);
    GameData	*GetData() const;
    void	GameEventGenerator();
    void	SaveScore();
    void	CalcScore();
  private:
    DLLoader<IGraphic>	*_loader;
    IGraphic		*_libgraph;
    GameData		*_data;
    bool		_ia;
    bool		_eventrandom;
    TimeCounter		_timer;
    EventManager	*_EvM;
    int			_turn;
  };

}

#endif /* !NIBBLER_HH_ */

