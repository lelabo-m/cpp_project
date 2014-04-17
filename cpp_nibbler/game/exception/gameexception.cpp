#include "gameexception.hpp"

SnakeGame::GameException::GameException(const char *msg)
{
  _msg = msg;
}

SnakeGame::GameException::~GameException() throw()
{
}

const char*     SnakeGame::GameException::what() const throw()
{
  return _msg.c_str();
}

SnakeGame::SysEventException::SysEventException(int type) : SnakeGame::GameException("System Event")
{
  _type = type;
}

SnakeGame::SysEventException::~SysEventException() throw()
{
}

int	SnakeGame::SysEventException::GetType() const
{
  return _type;
}
