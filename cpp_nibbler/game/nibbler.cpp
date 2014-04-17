#include <sstream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "gameexception.hpp"
#include "nibbler.hh"
#include "loader.hpp"
#include "event.hh"

SnakeGame::Nibbler::Nibbler(const std::string&, const std::string&)
{
  std::cout << "Build with mapfile" << std::endl;
}

SnakeGame::Nibbler::Nibbler(const std::string& lib, unsigned int len,
			    unsigned int width, unsigned int mode)
{
  std::cout << "Build with size" << std::endl;
  _data = new GameData();
  _data->_map = new Map(len, width, mode);
  Init(lib);
}

void	SnakeGame::Nibbler::Init(const std::string& lib)
{
  _loader = new DLLoader<IGraphic>(lib.c_str());
  _libgraph = _loader->LoadObject("entry_point");
  _data->_apples = 0;
  _data->_score = 0;
  _data->_end = false;
  _data->_player = new SnakeGame::Snake(0, 0, SNAKE_SPEED);
  _data->_player->AddBody(_data->_map->GetLength() / 2,
			  _data->_map->GetWidth() / 2, 0);
  _data->_player->PlaceBody(*_data);
  _data->_player->PlaceBody(*_data);
  _data->_player->PlaceBody(*_data);
  InitEventManager();
  _libgraph->Init(0, *_data);
  _turn = 0;
  _data->_incfood = _data->_map->GetLength() / 10 + 1;
  _data->_food = _data->_incfood;
  for (unsigned int i = 0; i < _data->_incfood; ++i)
    _data->_map->SetRandMapCell(APPLE);
}

SnakeGame::Nibbler::~Nibbler()
{
  _libgraph->Destroy();
}

bool	SnakeGame::Nibbler::GetIA() const
{
  return _ia;
}

bool	SnakeGame::Nibbler::GetER() const
{
  return _eventrandom;
}

SnakeGame::GameData*	SnakeGame::Nibbler::GetData() const
{
  return _data;
}

void	SnakeGame::Nibbler::SetIA(bool ia)
{
  _ia = ia;
}

void	SnakeGame::Nibbler::SetER(bool eventrandom)
{
  _eventrandom = eventrandom;
}

void	SnakeGame::Nibbler::SaveScore()
{
  std::ifstream score(".scoring", std::ios::in);
  if (score)
    {
      std::string content_1;
      std::string content_2;
      int	score_1 = -1;
      int	score_2 = -1;
      if (getline(score, content_1))
	{
	  std::istringstream buffer_1(content_1);
	  buffer_1 >> score_1;
	}
      if (getline(score, content_2))
	{
	  std::istringstream buffer_2(content_2);
	  buffer_2 >> score_2;
	}
      score.close();
      if (score_1 != -1 && score_2 != -1)
	{
	  std::ofstream scores(".scoring", std::ios::out | std::ios::trunc);
	  if (scores)
	    {
	      scores << _data->_score << std::endl;
	      if (score_2 > (int)_data->_score)
		scores << score_2 << std::endl;
	      else
		scores << _data->_score << std::endl;
	      scores.close();
	    }
	}
      else
	std::cout << "No score recorded !" << std::endl;
    }
  else
    std::cout << "No score recorded !" << std::endl;
}

void	SnakeGame::Nibbler::CalcScore()
{
  int		time = _timer.GetTime();
  _data->_score *= 10;
  if (_data->_apples)
    _data->_score += (time - (time / _data->_apples)) / 10;
}

void	SnakeGame::Nibbler::Launch()
{
  std::list<Event>	action;
  Event			ev;

  std::cout << "Game start" << std::endl;
  while (_data->_end == false)
    {
      ev.type = SnakeGame::ENONE;
      ev.value = 0;
      try
	{
	  ev = _libgraph->GetEvent();
	  if (ev.type == SnakeGame::EMOVE)
	    action.push_front(ev);
	}
      catch (SnakeGame::GraphicException &e)
	{
	  std::cout << e.what() << std::endl;
	}
      if (ev.type == SnakeGame::ESYSTEM)
	{
	  try
	    {
	      _EvM->PlayEvent(ev, *_data);
	    }
	  catch (SnakeGame::EventException &e)
	    {
	      break;
	    }
	  catch (SnakeGame::SysEventException &e)
	    {
	      std::cout << "Game interupted" << std::endl;
	      break;
	    }
	}
      if (_data->_player->Updateable(_timer.GetTime()))
	{
	  ++_turn;
	  _data->_player->Update(_timer.GetTime());
	  if (ev.type == SnakeGame::ENONE && action.size())
	    ev = action.front();
	  try
	    {
	      _EvM->PlayEvent(ev, *_data);
	      action.clear();
	    }
	  catch (SnakeGame::SysEventException &e)
	    {
	      std::cout << "Game interupted" << std::endl;
	      break;
	    }
	  catch (SnakeGame::ColliderException &e)
	    {
	      SnakeGame::Event	col;
	      col.type = EOBJ;
	      col.value = (int)(e.GetType());
	      try
		{
		  _EvM->PlayEvent(col, *_data);
		}
	      catch (SnakeGame::EventException &e)
		{
		  _data->_end = true;
		  continue;
		}
	    }
	  catch (SnakeGame::EventException &e)
	    {
	      _data->_end = true;
	      continue;
	    }
	}
      GameEventGenerator();
      try
	{
	  _libgraph->Display(*_data);
	}
      catch (SnakeGame::GraphicException &e)
	{
	  std::cout << e.what() << std::endl;
	}
    }
  CalcScore();
  SaveScore();
  std::cout << "Game end" << std::endl;
  std::cout << "Game Time : " << _timer.GetTime() << std::endl;
  std::cout << "Score : " << _data->_score << std::endl;
}

void	SnakeGame::Nibbler::GameEventGenerator()
{
  if (_data->_food <= 0)
    {
      unsigned int	food = rand() % _data->_incfood;
      for (unsigned int i = 0; i < food; ++i)
	_data->_map->SetRandMapCell(APPLE);
      _data->_food = food;
    }
  if (_turn % 40 == 0)
    {
      ++_turn;
      Event	ev;
      ev.type = SnakeGame::EEVENT;
      ev.value = 0;
      try
  	{
  	  _EvM->PlayEvent(ev, *_data);
  	}
      catch (SnakeGame::EventException &e)
  	{
  	  std::cout << "Bad event" << std::endl;
  	}
    }
}
