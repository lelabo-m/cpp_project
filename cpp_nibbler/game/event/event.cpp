#include <iostream>
#include "gameexception.hpp"
#include "event.hh"

// ###### EventTree ######
SnakeGame::EventTree::EventTree()
{
}

SnakeGame::EventTree::~EventTree()
{
}

void	SnakeGame::EventTree::AddEvent(const Event& ev, Fonctor<SnakeGame::Snake, GameData &>* func)
{
  _eventlist[ev.value] = func;
}

void	SnakeGame::EventTree::DelEvent(const Event& ev)
{
  _eventlist[ev.value] = 0;
}

void	SnakeGame::EventTree::PlayEvent(const Event& ev, GameData& data)
{
  Fonctor<SnakeGame::Snake, GameData &>* func;

  func = _eventlist[ev.value];
  if (!func)
    throw SnakeGame::EventException("Event doesn't exist");
  (*func)(data);
}
// ###### EventTree ######

// ###### EventManager ######
SnakeGame::EventManager::EventManager()
{
}

SnakeGame::EventManager::~EventManager()
{
}

void	SnakeGame::EventManager::AddTree(const Event& ev, EventTree *tree)
{
  _treelist[ev.type] = tree;
}

void	SnakeGame::EventManager::DelTree(const Event& ev)
{
  _treelist[ev.type] = 0;
}

void	SnakeGame::EventManager::PlayEvent(const Event& ev, GameData& data)
{
  EventTree			*tree;

  //  std::cout << "event = " << ev.type << " " << ev.value << std::endl;
  if (ev.type == SnakeGame::ENONE)
    {
      Event	ev2;
      ev2.type = SnakeGame::EMOVE;
      tree = _treelist[ev2.type];
    }
  else
    tree = _treelist[ev.type];
  if (!tree)
    throw SnakeGame::EventException("EventTree doesn't exist");
  tree->PlayEvent(ev, data);
}
// ###### EventManager ######
