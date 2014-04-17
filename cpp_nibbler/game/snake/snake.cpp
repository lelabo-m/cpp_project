#include <iostream>
#include <algorithm>
#include "gameexception.hpp"
#include "event.hh"
#include "nibbler.hh"
#include "snake.hh"
#include "map.hh"

SnakeGame::Snake::Snake(int time, int id, int speed)
{
  _lastupdate = time;
  _id = id;
  _speed = speed;
  _direction = (rand() % 4);
}

void	SnakeGame::Snake::SnakeDestroyBody(SnakeBody *elem)
{
  delete elem;
}

SnakeGame::Snake::~Snake()
{
  std::for_each(_body.begin(), _body.end(), &SnakeGame::Snake::SnakeDestroyBody);
}

bool	SnakeGame::Snake::Updateable(int time)
{
  if (time - _lastupdate >= _speed)
    return true;
  return false;
}

void	SnakeGame::Snake::Update(int time)
{
  _lastupdate = time;
}

int	SnakeGame::Snake::GetSpeed() const
{
  return _speed;
}

int	SnakeGame::Snake::GetId() const
{
  return _id;
}

void	SnakeGame::Snake::SetSpeed(int speed)
{
  if (speed >= 0)
    _speed = speed;
}

void	SnakeGame::Snake::SetId(int id)
{
  _id = id;
}

void	SnakeGame::Snake::AddBody(float x, float y, int statut)
{
  SnakeBody	*elem = new SnakeBody();
  elem->x = x;
  elem->y = y;
  elem->statut = statut;
  _body.push_front(elem);
}

void	SnakeGame::Snake::PlaceBody(GameData& data)
{
  SnakeBody*	front = _body.front();
  float		x;
  float		y;

  x = front->x;
  y = front->y;
  if (_direction == 0)
      x = front->x - 1.0;
  else if (_direction == 1)
      y = front->y + 1.0;
  else if (_direction == 2)
      x = front->x + 1.0;
  else if (_direction == 3)
      y = front->y - 1.0;
  if (data._map->GetMapCell((int)x, (int)y) == APPLE)
    {
      data._map->SetMapCell((int)x, (int)y, VOID);
      data._food -= 1;
    }
  AddBody(x, y, 0);
  front->statut = 1;
}


std::list<SnakeGame::SnakeBody *>        &SnakeGame::Snake::GetBody()
{
  return _body;
}

bool	SnakeGame::Snake::BodyBroken()
{
  SnakeBody	*ref = _body.front();

  for(std::list<SnakeGame::SnakeBody *>::iterator it = _body.begin(); it != _body.end(); ++it)
    {
      if (*it != ref)
	{
	  if (((unsigned int)ref->x == (unsigned int)((*it)->x))
	      && ((unsigned int)ref->y == (unsigned int)((*it)->y)))
	    return true;
	}
    }
  return false;
}

// Event Method
void	SnakeGame::Snake::EventClose(SnakeGame::GameData&)
{
  throw SysEventException(0);
}

void	SnakeGame::Snake::EventPauseON(SnakeGame::GameData&)
{
  throw SysEventException(1);
}

void	SnakeGame::Snake::EventPauseOFF(SnakeGame::GameData&)
{
  throw SysEventException(1);
}

void	SnakeGame::Snake::MoveLeft(SnakeGame::GameData& data)
{
  SnakeBody	*end = _body.back();
  SnakeBody	*front = _body.front();
  float		x;
  float		y;

  x = front->x;
  y = front->y;
  _direction -= 1;
  if (_direction < 0)
    _direction += 4;
  if (_direction == 0)
      x = front->x - 1.0;
  else if (_direction == 1)
      y = front->y + 1.0;
  else if (_direction == 2)
      x = front->x + 1.0;
  else if (_direction == 3)
      y = front->y - 1.0;
  MapCell	cell = data._map->GetMapCell((unsigned int)x, (unsigned int)y);
  if (cell != SnakeGame::VOID)
    throw ColliderException(cell);
  end->x = x;
  end->y = y;
  _body.pop_back();
  _body.push_front(end);
  if (BodyBroken())
    throw EventException("Snake die");
}

void	SnakeGame::Snake::MoveForward(SnakeGame::GameData& data)
{
  SnakeBody	*end = _body.back();
  SnakeBody	*front = _body.front();
  float		x;
  float		y;
  x = front->x;
  y = front->y;
  if (_direction == 0)
      x = front->x - 1.0;
  else if (_direction == 1)
      y = front->y + 1.0;
  else if (_direction == 2)
      x = front->x + 1.0;
  else if (_direction == 3)
      y = front->y - 1.0;
  MapCell	cell = data._map->GetMapCell((unsigned int)x, (unsigned int)y);
  if (cell != SnakeGame::VOID)
    throw ColliderException(cell);
  end->x = x;
  end->y = y;
  _body.pop_back();
  _body.push_front(end);
  if (BodyBroken())
    throw EventException("Snake die");
}

void	SnakeGame::Snake::MoveRight(SnakeGame::GameData& data)
{
  SnakeBody	*end = _body.back();
  SnakeBody	*front = _body.front();
  float		x;
  float		y;

  x = front->x;
  y = front->y;
  _direction += 1;
  _direction %= 4;
  if (_direction == 0)
      x = front->x - 1.0;
  else if (_direction == 1)
      y = front->y + 1.0;
  else if (_direction == 2)
      x = front->x + 1.0;
  else if (_direction == 3)
      y = front->y - 1.0;
  MapCell	cell = data._map->GetMapCell((unsigned int)x, (unsigned int)y);
  if (cell != SnakeGame::VOID)
    throw ColliderException(cell);
  end->x = x;
  end->y = y;
  _body.pop_back();
  _body.push_front(end);
  if (BodyBroken())
    throw EventException("Snake die");
}

int         SnakeGame::Snake::GetDirection() const
{
  return _direction;
}

void	SnakeGame::Snake::EatApple(GameData& data)
{
  SnakeBody*	front = _body.front();
  float		x;
  float		y;

  x = front->x;
  y = front->y;
  if (_direction == 0)
      x = front->x - 1.0;
  else if (_direction == 1)
      y = front->y + 1.0;
  else if (_direction == 2)
      x = front->x + 1.0;
  else if (_direction == 3)
      y = front->y - 1.0;
  data._map->SetMapCell((int)x, (int)y, VOID);
  AddBody(x, y, 0);
  front->statut = 1;
  data._food -= 1;
  data._apples += 1;
  data._score += 10;
  if (!(data._apples % 5))
    {
      data._score += ((rand() + 1) % 100) * 100;
    }
  if (!(data._apples % 3) && _speed > 10)
    _speed -= 10;
}

void	SnakeGame::Snake::PopWall(GameData& data)
{
  unsigned int	x;
  unsigned int	y;

  data._map->GetRandPosition(&x, &y);
  data._map->SetMapCell(x, y, WALL);
}

