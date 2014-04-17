#ifndef GAMEEXCEPTION_HH_
# define GAMEEXCEPTION_HH_

#include <string>
#include "map.hh"

namespace SnakeGame
{
  class GameException : public std::exception
  {
  public:
    GameException(const char *msg = "");
    virtual ~GameException() throw();
    const char *  what() const throw();
  private:
    std::string	_msg;
  };

  class SysEventException : public GameException
  {
  public:
    SysEventException(int);
    ~SysEventException() throw();
    int	GetType() const;
    using GameException::what;
  private:
    int		_type;
  };

  class GraphicException : public GameException
  {
  public:
    GraphicException(const std::string& msg) : GameException(msg.c_str()) {};
    ~GraphicException() throw() {};
    using GameException::what;
  };

  class EventException : public GameException
  {
  public:
    EventException(const std::string& msg) : GameException(msg.c_str()) {};
    ~EventException() throw() {};
    using GameException::what;
  };

  class ColliderException : public GameException
  {
  public:
    ColliderException(MapCell obj) : GameException("Collision with object") , _obj(obj) {};
    ~ColliderException() throw() {};
    using GameException::what;
    MapCell	GetType() const
    {
      return _obj;
    }
  private:
    MapCell	_obj;
  };
}

#endif /* !GAMEEXCEPTION_HH_ */

