#include <iostream>
#include <exception>
#include "nibbler.hh"
#include "Graphic.hh"
#include "event.hh"
#include "gameexception.hpp"

Graphic::Graphic()
{
  _keymap[sf::Keyboard::Up] = (unsigned int)UP;
  _keymap[sf::Keyboard::Down] = (unsigned int)DOWN;
  _keymap[sf::Keyboard::Right] = (unsigned int)RIGHT;
  _keymap[sf::Keyboard::Left] = (unsigned int)LEFT;
  _keymap[sf::Keyboard::Space] = (unsigned int)SPACE;
  _keymap[sf::Keyboard::Escape] = (unsigned int)ESC;
  _keymap[sf::Keyboard::P] = (unsigned int)PLAY_PAUSE;
  _keymap[sf::Keyboard::M] = (unsigned int)MUSIC;
  _keymap[sf::Keyboard::Return] = (unsigned int)ENTER;
  _keymap[sf::Keyboard::BackSpace] = (unsigned int)BACKSPACE;
}

Graphic::~Graphic()
{

}

void			Graphic::Init(int keyboard, const SnakeGame::GameData& data)
{
  int   coeff = 20;
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  _keyboard = keyboard;
  if (getenv("TERM") == NULL)
    throw SnakeGame::GraphicException("Open window fail!");
  sf::VideoMode	video(data._map->GetLength() * coeff, data._map->GetWidth() * coeff);
  _win = new sf::RenderWindow(video, WINNAME, sf::Style::Default, settings);
  if (!_win)
    throw SnakeGame::GraphicException("Open window fail!");
  _win->clear();
  if (!(textures["yoshi_egg"].loadFromFile("./imgs/yoshi_egg.png")) ||
      !(textures["yoshi_h"].loadFromFile("./imgs/yoshi_h.png")) ||
      !(textures["yoshi_b"].loadFromFile("./imgs/yoshi_b.png")) ||
      !(textures["yoshi_d"].loadFromFile("./imgs/yoshi_d.png")) ||
      !(textures["yoshi_g"].loadFromFile("./imgs/yoshi_g.png")) ||
      !(textures["wall"].loadFromFile("./imgs/wall.png")) ||
      !(textures["map"].loadFromFile("./imgs/map.png")) ||
      !(textures["apple"].loadFromFile("./imgs/apple.png")))
    {
      throw new std::exception();
    }
  textures["yoshi_egg"].setSmooth(true);
  textures["yoshi"].setSmooth(true);
  textures["wall"].setSmooth(true);
  textures["map"].setSmooth(true);
  sprites["yoshi_h"].setTexture(textures["yoshi_h"]);
  sprites["yoshi_h"].setScale(sf::Vector2f(1.2*coeff/34.0, 1.0*coeff/39.0));
  sprites["yoshi_b"].setTexture(textures["yoshi_b"]);
  sprites["yoshi_b"].setScale(sf::Vector2f(1.2*coeff/30.0, 1.0*coeff/41.0));
  sprites["yoshi_d"].setTexture(textures["yoshi_d"]);
  sprites["yoshi_d"].setScale(sf::Vector2f(1.2*coeff/40.0, 1.0*coeff/41.0));
  sprites["yoshi_g"].setTexture(textures["yoshi_g"]);
  sprites["yoshi_g"].setScale(sf::Vector2f(1.2*coeff/40.0, 1.0*coeff/41.0));
  sprites["yoshi_egg"].setTexture(textures["yoshi_egg"]);
  sprites["yoshi_egg"].setScale(sf::Vector2f(1.*coeff/200.0, 1.0*coeff/240.0));
  sprites["wall"].setTexture(textures["wall"]);
  sprites["wall"].setScale(sf::Vector2f(1.0*coeff/1754.0, 1.0*coeff/1753.0));
  sprites["apple"].setTexture(textures["apple"]);
  sprites["apple"].setScale(sf::Vector2f(1.0*coeff/483.0, 1.0*coeff/480.0));
  sprites["map"].setTexture(textures["map"]);
  sprites["map"].setScale(sf::Vector2f((coeff * data._map->GetLength())/2654.0, (coeff * data._map->GetWidth())/1254.0));
  sprites["map"].setColor(sf::Color(255, 255, 255, 40));
}

void		Graphic::Display(const SnakeGame::GameData &data)
{
  int   size = data._map->GetLength() * data._map->GetWidth();
  int   coeff = 20;
  int	direction = -1;

  if (!_win->isOpen())
    return ;
  _win->clear(sf::Color::Black);
  _win->draw(sprites["map"]);
  for (int i = 0; i < size; i+=1)
    {
      if (data._map->GetMapCell(i) == SnakeGame::WALL)
	{
	  sprites["wall"].setPosition(i / data._map->GetWidth()*coeff, i % data._map->GetWidth()*coeff);
	  _win->draw(sprites["wall"]);
	}
      else if (data._map->GetMapCell(i) == SnakeGame::APPLE)
	{
	  sprites["apple"].setPosition(i / data._map->GetWidth()*coeff, i % data._map->GetWidth()*coeff);
	  _win->draw(sprites["apple"]);
	}
    }
  for(std::list<SnakeGame::SnakeBody *>::iterator it = data._player->GetBody().begin(); it != data._player->GetBody().end(); ++it)
  {
    if (it == data._player->GetBody().begin())
      {
	direction += data._player->GetDirection();
	if (direction < 0)
	  direction += 4;
	switch (direction)
	  {
	  case 0:
	    sprites["yoshi_b"].setPosition((*it)->x*coeff, (*it)->y*coeff);
	    _win->draw(sprites["yoshi_b"]);
	    break;
	  case 1:
	    sprites["yoshi_d"].setPosition((*it)->x*coeff, (*it)->y*coeff);
	    _win->draw(sprites["yoshi_d"]);
	    break;
	  case 2:
	    sprites["yoshi_h"].setPosition((*it)->x*coeff, (*it)->y*coeff);
	    _win->draw(sprites["yoshi_h"]);
	    break;
	  case 3:
	    sprites["yoshi_g"].setPosition((*it)->x*coeff, (*it)->y*coeff);
	    _win->draw(sprites["yoshi_g"]);
	    break;
	  }
      }
    else
      {
	sprites["yoshi_egg"].setPosition((*it)->x*coeff, (*it)->y*coeff);
	_win->draw(sprites["yoshi_egg"]);
      }
  }
  _win->display();
}

SnakeGame::Event	Graphic::GetEvent()
{
  SnakeGame::Event	ev;
  sf::Event		event;

  ev.type = SnakeGame::ENONE;
  ev.value = 0;
  while (_win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
	{
	  ev.type = SnakeGame::ESYSTEM;
	  ev.value = 0;
	}
      else if (event.type == sf::Event::KeyReleased)
      	{
	  ev.type = SnakeGame::EMOVE;
	  ev.value = _keymap[event.key.code];
      	}
    }
  return ev;
}

void			Graphic::Destroy()
{
  _win->close();
}

extern "C" IGraphic	*entry_point()
{
  return (new Graphic());
}
