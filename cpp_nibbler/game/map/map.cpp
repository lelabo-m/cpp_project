#include <iostream>
#include <cstdlib>
#include "map.hh"

SnakeGame::Map::Map(unsigned int length, unsigned int width, unsigned int mode)
{
  _length = length;
  _width = width;
  if (mode == 0)
    GenMap();
  else if (mode == 1)
    GenRandMap();
}

SnakeGame::Map::Map(const std::string&)
{

}

void	SnakeGame::Map::GenMap()
{
  unsigned int	size = _length * _width;

  for (unsigned int i = 0; i < size; ++i)
    _map.push_back(VOID);
  for (unsigned int i = 0; i < size; ++i)
    {
      if (i < _width || i >= size - _width || !(i % _width) || !((i + 1) % _width))
	SetMapCell(i / _width, i % _width, WALL);
    }
}

void	SnakeGame::Map::GenRandMap()
{
  unsigned int	size = _length * _width;

  for (unsigned int i = 0; i < size; ++i)
    _map.push_back(VOID);
  for (unsigned int i = 0; i < START_WALL; ++i)
    SetRandMapCell(WALL);
  for (unsigned int i = 0; i < START_FOOD; ++i)
    SetRandMapCell(APPLE);
  for (unsigned int i = 0; i < size; ++i)
    if (i < _width || i >= size - _width || !(i % _width) || !((i + 1) % _width))
      SetMapCell(i / _width, i % _width, WALL);
}

void	SnakeGame::Map::SetMapCell(unsigned int x, unsigned int y, const SnakeGame::MapCell value)
{
  _map[x * _width + y] = value;
}

void	SnakeGame::Map::SetRandMapCell(MapCell value)
{
  unsigned int	random = rand() % (_width * (_length - 2)) + _width;
  unsigned int	size = _length * _width;

  if (!(random < _width || random >= size - _width ||
	!(random % _width) || !((random + 1) % _width)))
    _map[random] = value;
  else if (random % _width == 0)
    _map[random + 1] = value;
  else
    _map[random - 1] = value;
}

void	SnakeGame::Map::GetRandPosition(unsigned int *x, unsigned int *y)
{
  unsigned int	size = _length * _width;
  int	end;

  end = 0;
  *x = 0;
  *y = 0;
  while (end < 1000)
    {
      unsigned int	random = (_width / 10 + _length + 10) + rand()
	% ((_width * (_length - 2) + _width));
      if (random % _width == 0)
	random += 1;
      else if (!(random < _width || random >= size - _width ||
		 !(random % _width) || !((random + 1) % _width)))
	random -= 1;
      if (_map[random] == VOID)
	{
	  *x = random / _length;
	  *y = random % _width;
	  break;
	}
      ++end;
    }
}

SnakeGame::MapCell	SnakeGame::Map::GetMapCell(unsigned int x, unsigned int y) const
{
  return _map[x * _width + y];
}

SnakeGame::MapCell	SnakeGame::Map::GetMapCell(unsigned int pos) const
{
  return _map[pos];
}

unsigned int	SnakeGame::Map::GetLength() const
{
  return _length;
}

unsigned int	SnakeGame::Map::GetWidth() const
{
  return _width;
}

SnakeGame::Map::~Map()
{

}

void			SnakeGame::Map::Dump() const
{
  std::cout << "len= " << _length << " width= " << _width<< std::endl;
  for (unsigned int x = 0; x < _length; ++x)
    {
      for (unsigned int y = 0; y < _width; ++y)
	{
	  std::cout << _map[x * _width + y];
	  std::cout << " ";
	}
      std::cout << std::endl;
    }
}
