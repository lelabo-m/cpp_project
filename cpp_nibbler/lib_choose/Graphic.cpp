#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <exception>
#include "Graphic.hh"

Graphic::Graphic()
{
  l_green = 0;
  l_blue = 0;
  l_red = 0;
  l_star = 0;
  green_activate = false;
  blue_activate = false;
  red_activate = false;
  star_activate = false;
  nb_1 = "-1";
  nb_2 = "-1";
}

Graphic::~Graphic()
{

}

void			Graphic::Init()
{
  int	coeff	= 32;
  sf::ContextSettings settings;

  settings.antialiasingLevel = 8;
  _win = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), WINNAME, sf::Style::Default, settings);
  if (!_win)
    throw new std::exception();
  _win->clear();
  if (!(textures["void_block"].loadFromFile("./imgs/void_block.png")) ||
      !(textures["green_pipe"].loadFromFile("./imgs/green_pipe.png")) ||
      !(textures["blue_pipe"].loadFromFile("./imgs/blue_pipe.png")) ||
      !(textures["red_pipe"].loadFromFile("./imgs/red_pipe.png")) ||

      !(textures["green_mush"].loadFromFile("./imgs/green_mush.png")) ||
      !(textures["blue_mush"].loadFromFile("./imgs/blue_mush.png")) ||
      !(textures["red_mush"].loadFromFile("./imgs/red_mush.png")) ||

      !(textures["sfml"].loadFromFile("./imgs/sfml.png")) ||
      !(textures["allegro"].loadFromFile("./imgs/allegro.png")) ||
      !(textures["opengl"].loadFromFile("./imgs/opengl.png")) ||
      !(textures["wall"].loadFromFile("./imgs/block_quest.png")) ||
      !(textures["map"].loadFromFile("./imgs/map_choose.jpg")) ||
      !(textures["star"].loadFromFile("./imgs/star.png")))
    {
      throw new std::exception();
    }
  if (!font.loadFromFile("./lib_choose/font.ttf"))
    throw new std::exception();
  textures["void_block"].setSmooth(true);
  textures["yoshi"].setSmooth(true);
  textures["wall"].setSmooth(true);
  textures["map"].setSmooth(true);
  textures["green_pipe"].setSmooth(true);
  textures["blue_pipe"].setSmooth(true);
  textures["red_pipe"].setSmooth(true);
  textures["green_mush"].setSmooth(true);
  textures["blue_mush"].setSmooth(true);
  textures["red_mush"].setSmooth(true);
  textures["sfml"].setSmooth(true);
  textures["opengl"].setSmooth(true);
  textures["allegro"].setSmooth(true);
  textures["star"].setSmooth(true);
  textures["void_block"].setSmooth(true);

  sprites["green_pipe"].setTexture(textures["green_pipe"]);
  sprites["green_pipe"].setScale(sf::Vector2f(1.0/5.0, 1.0/5.0));
  sprites["blue_pipe"].setTexture(textures["blue_pipe"]);
  sprites["blue_pipe"].setScale(sf::Vector2f(1.0/5.0, 1.0/5.0));
  sprites["red_pipe"].setTexture(textures["red_pipe"]);
  sprites["red_pipe"].setScale(sf::Vector2f(1.0/5.0, 1.0/5.0));

  sprites["green_mush"].setTexture(textures["green_mush"]);
  sprites["green_mush"].setScale(sf::Vector2f(1.0/8.0, 1.0/8.0));
  sprites["blue_mush"].setTexture(textures["blue_mush"]);
  sprites["blue_mush"].setScale(sf::Vector2f(1.0/8.0, 1.0/8.0));
  sprites["red_mush"].setTexture(textures["red_mush"]);
  sprites["red_mush"].setScale(sf::Vector2f(1.0/8.0, 1.0/8.0));

  sprites["sfml"].setTexture(textures["sfml"]);
  sprites["sfml"].setScale(sf::Vector2f(0.7, 0.7));
  sprites["allegro"].setTexture(textures["allegro"]);
  sprites["allegro"].setScale(sf::Vector2f(0.7, 0.7));
  sprites["opengl"].setTexture(textures["opengl"]);
  sprites["opengl"].setScale(sf::Vector2f(0.7, 0.7));
  sprites["void_block"].setTexture(textures["void_block"]);
  sprites["void_block"].setScale(sf::Vector2f(5.0*coeff/480.0, 5.0*coeff/480.0));
  sprites["wall"].setTexture(textures["wall"]);
  sprites["wall"].setScale(sf::Vector2f(5.0*coeff/480.0, 5.0*coeff/480.0));
  sprites["star"].setTexture(textures["star"]);
  sprites["star"].setScale(sf::Vector2f(4.0*coeff/400.0, 4.0*coeff/381.0));
  sprites["map"].setTexture(textures["map"]);
  sprites["map"].setScale(sf::Vector2f(1920.0/2560.0, 1080.0/1600.0));
  sprites["map"].setColor(sf::Color(255, 255, 255, 120));

  std::ifstream score(".scoring", std::ios::in);
  if (score)
    {
      getline(score, nb_1);
      getline(score, nb_2);
      score.close();
    }
}

void		Graphic::Display()
{
  int	coeff	= 32;

  _win->clear(sf::Color::Black);
  _win->draw(sprites["map"]);
  if (star_activate)
    {
      if ((float)l_star < 4.0*coeff)
	{
	  sprites["star"].setPosition(1920.0/2.0 - 4.0*coeff/2.0, 1080.0/2.0 - coeff*5.0/2 - l_star);
	  _win->draw(sprites["star"]);
	  l_star++;
	}
      else
	{
	  sprites["star"].setPosition(1920.0/2.0 - coeff*4.0/2.0, 1080.0/2.0 - coeff*5.0/2 - l_star);
	  _win->draw(sprites["star"]);
	}
      sprites["void_block"].setPosition(1920.0/2.0 - coeff*5.0/2.0, 1080.0/2.0 - coeff*5.0/2);
      _win->draw(sprites["void_block"]);
    }
  else
    {
      sprites["wall"].setPosition(1920.0/2.0 - coeff*5.0/2, 1080.0/2.0 - coeff*5.0/2);
      _win->draw(sprites["wall"]);
    }

  if (green_activate && (float)l_green < 870.0 / 8.0)
    {
      sprites["green_mush"].setPosition(1.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_green);
      _win->draw(sprites["green_mush"]);
      l_green++;
    }
  else if (green_activate)
    {
      sprites["green_mush"].setPosition(1.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_green);
      _win->draw(sprites["green_mush"]);
    }
  if (blue_activate && (float)l_blue < 870.0 / 8.0)
    {
      sprites["blue_mush"].setPosition(2.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_blue);
      _win->draw(sprites["blue_mush"]);
      l_blue++;
    }
  else if (blue_activate)
    {
      sprites["blue_mush"].setPosition(2.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_blue);
      _win->draw(sprites["blue_mush"]);
    }
  if (red_activate && (float)l_red < 870.0 / 8.0)
    {
      sprites["red_mush"].setPosition(3.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_red);
      _win->draw(sprites["red_mush"]);
      l_red++;
    }
  else if (red_activate)
    {
      sprites["red_mush"].setPosition(3.0*1920.0/4.0 - 876.0/16.0, 1080.0 - 2713.0/10.0 - l_red);
      _win->draw(sprites["red_mush"]);
    }

  sprites["green_pipe"].setPosition(1.0*1920.0/4.0 - 108.7, 1080.0 - 2713.0/10.0);
  _win->draw(sprites["green_pipe"]);
  sprites["allegro"].setPosition(1.0*1920.0/4.0 - 217.0*0.7/2.0, 1080.0 - 2713.0/20.0 - 35.5);
  _win->draw(sprites["allegro"]);
  sprites["blue_pipe"].setPosition(2.0*1920.0/4.0 - 108.7, 1080.0 - 2713.0/10.0);
  _win->draw(sprites["blue_pipe"]);
  sprites["opengl"].setPosition(2.0*1920.0/4.0 - 217.0*0.7/2.0, 1080.0 - 2713.0/20.0 - 50.0);
  _win->draw(sprites["opengl"]);
  sprites["red_pipe"].setPosition(3.0*1920.0/4.0 - 108.7, 1080.0 - 2713.0/10.0);
  _win->draw(sprites["red_pipe"]);
  sprites["sfml"].setPosition(3.0*1920.0/4.0 - 217.0*0.7/2.0, 1080.0 - 2713.0/20.0 - 35.0);
  _win->draw(sprites["sfml"]);
  if (nb_1 != "-1" && nb_2 != "-1")
    {
      sf::Text last;
      last.setFont(font);
      last.setString("Last Score : "+nb_1);
      last.setCharacterSize(25);
      last.setColor(sf::Color::White);
      sf::Text best;
      best.setFont(font);
      best.setString("Best Score : "+nb_2);
      best.setCharacterSize(25);
      best.setColor(sf::Color::White);
      last.setPosition(1550, 100);
      best.setPosition(1550, 150);
      _win->draw(last);
      _win->draw(best);
    }
  _win->display();
}

int	Graphic::GetEvent()
{
  int	coeff	= 32;
  sf::Event		event;

  while (_win->pollEvent(event))
    {
      if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
	{
	  return (0);
	}
      else if (event.type == sf::Event::MouseButtonPressed)
	{
	  if (event.mouseButton.button == sf::Mouse::Left)
	    {
	      if (event.mouseButton.x > 1920.0/4.0 - 108.7
		  && event.mouseButton.x < 1920.0/4.0 + 108.7
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0
		  && event.mouseButton.y < 1080.0)
		green_activate = true;
	      if (event.mouseButton.x > 2.0*1920.0/4.0 - 108.7
		  && event.mouseButton.x < 2.0*1920.0/4.0 + 108.7
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0
		  && event.mouseButton.y < 1080.0)
		blue_activate = true;
	      if (event.mouseButton.x > 3.0*1920.0/4.0 - 108.7
		  && event.mouseButton.x < 3.0*1920.0/4.0 + 108.7
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0
		  && event.mouseButton.y < 1080.0)
		red_activate = true;
	      if (event.mouseButton.x > 1920.0/2.0 - coeff*5.0/2
		  && event.mouseButton.x < 1920.0/2.0 + coeff*5.0/2
		  && event.mouseButton.y > 1080.0/2.0 - coeff*5.0/2
		  && event.mouseButton.y < 1080.0/2.0 + coeff*5.0/2)
		star_activate = true;
	      if (event.mouseButton.x > 1920.0/4.0 - 876.0/16.0
		  && event.mouseButton.x < 1920.0/4.0 + 876.0/16.0
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0 - l_green
		  && event.mouseButton.y < 1080.0 - 2713.0/10.0)
		return (2);
	      if (event.mouseButton.x > 2.0*1920.0/4.0 - 876.0/16.0
		  && event.mouseButton.x < 2.0*1920.0/4.0 + 876.0/16.0
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0 - l_blue
		  && event.mouseButton.y < 1080.0 - 2713.0/10.0)
		return (3);
	      if (event.mouseButton.x > 3.0*1920.0/4.0 - 876.0/16.0
		  && event.mouseButton.x < 3.0*1920.0/4.0 + 876.0/16.0
		  && event.mouseButton.y > 1080.0 - 2713.0/10.0 - l_red
		  && event.mouseButton.y < 1080.0 - 2713.0/10.0)
		return (4);
	      if (event.mouseButton.x > 1920.0/2.0 - 4.0*coeff/2.0
		  && event.mouseButton.x < 1920.0/2.0 + 4.0*coeff/2.0
		  && event.mouseButton.y > 1080.0/2.0 - coeff*5.0/2 - l_star
		  && event.mouseButton.y < 1080.0/2.0 - coeff*5.0/2)
		return (1);
	    }
	}
    }
  return -1;
}

void			Graphic::Destroy()
{
  _win->close();
}
