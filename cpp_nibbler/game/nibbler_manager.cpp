#include "nibbler.hh"
#include "event.hh"

SnakeGame::Event	InitEvent(SnakeGame::EventType type, int value = 0)
{
  SnakeGame::Event	ev;

  ev.type = type;
  ev.value = value;
  return ev;
}

Fonctor<SnakeGame::Snake, SnakeGame::GameData&>*
InitFonctor(SnakeGame::Snake *player, void (SnakeGame::Snake::*func)(SnakeGame::GameData&))
{
  return (new Fonctor<SnakeGame::Snake, SnakeGame::GameData&>(player, func));
}

void		PutInTree(SnakeGame::Event ev, SnakeGame::EventTree *tree, SnakeGame::Snake *player,
			  void (SnakeGame::Snake::*func)(SnakeGame::GameData&))
{

  Fonctor<SnakeGame::Snake, SnakeGame::GameData&>* f = InitFonctor(player, func);
  tree->AddEvent(ev, f);
}

void	SnakeGame::Nibbler::InitEventManager()
{
  _EvM = new EventManager();
  EventTree	*movetree = new EventTree();
  EventTree	*systree = new EventTree();
  EventTree	*objtree = new EventTree();
  EventTree	*evtree = new EventTree();

  // SYSTREE
  PutInTree(InitEvent(SnakeGame::ESYSTEM, 0), systree,
	    _data->_player, &Snake::EventClose);
  PutInTree(InitEvent(SnakeGame::ESYSTEM, 1), systree,
	    _data->_player, &Snake::EventPauseON);
  PutInTree(InitEvent(SnakeGame::ESYSTEM, 2), systree,
	    _data->_player, &Snake::EventPauseOFF);
  _EvM->AddTree(InitEvent(SnakeGame::ESYSTEM), systree);
  // MOVETREE
  PutInTree(InitEvent(SnakeGame::EMOVE, 5), movetree,
	    _data->_player, &Snake::EventClose);
  PutInTree(InitEvent(SnakeGame::EMOVE, 6), movetree,
	    _data->_player, &Snake::EventPauseON);
  PutInTree(InitEvent(SnakeGame::EMOVE, 1), movetree,
	    _data->_player, &Snake::MoveLeft);
  PutInTree(InitEvent(SnakeGame::EMOVE, 3), movetree,
	    _data->_player, &Snake::MoveLeft);
  PutInTree(InitEvent(SnakeGame::EMOVE, 2), movetree,
	    _data->_player, &Snake::MoveRight);
  PutInTree(InitEvent(SnakeGame::EMOVE, 4), movetree,
	    _data->_player, &Snake::MoveRight);
  PutInTree(InitEvent(SnakeGame::EMOVE, 0), movetree,
	    _data->_player, &Snake::MoveForward);
  _EvM->AddTree(InitEvent(SnakeGame::EMOVE), movetree);
  // OBJTREE
  PutInTree(InitEvent(SnakeGame::EOBJ, (int)SnakeGame::APPLE), objtree,
	    _data->_player, &Snake::EatApple);
  _EvM->AddTree(InitEvent(SnakeGame::EOBJ), objtree);
  // EVENTTREE
  PutInTree(InitEvent(SnakeGame::EEVENT, 0), evtree,
	    _data->_player, &Snake::PopWall);
  _EvM->AddTree(InitEvent(SnakeGame::EEVENT), evtree);
}
