#ifndef EVENT_HH_
# define EVENT_HH_

#include <map>
#include <string>
#include "nibbler.hh"
#include "snake.hh"
#include "fonctor.hpp"

namespace SnakeGame
{
  enum EventType {ENONE, EMOVE, EOBJ, ESYSTEM, EEVENT};

  struct Event
  {
    EventType		type;
    unsigned int	value;
  };

  class	IEventTree
  {
  public:
    virtual ~IEventTree() {};
    virtual void	AddEvent(const Event&, Fonctor<Snake, GameData&>*) = 0;
    virtual void	DelEvent(const Event&) = 0;
    virtual void	PlayEvent(const Event&, GameData&) = 0;
  };

  class EventTree : public IEventTree
  {
  public:
    EventTree();
    ~EventTree();
    void	AddEvent(const Event&, Fonctor<Snake, GameData&>*);
    void	DelEvent(const Event&);
    void	PlayEvent(const Event&, GameData&);
  private:
    std::map<unsigned int, Fonctor<Snake, GameData&>* >	_eventlist;
  };

  class EventManager
  {
  public:
    EventManager();
    ~EventManager();
    void	AddTree(const Event&, EventTree *);
    void	DelTree(const Event&);
    void	PlayEvent(const Event&, GameData&);
  private:
    std::map<EventType, EventTree *>	_treelist;
  };
}

#endif /* !EVENT_HH_ */

