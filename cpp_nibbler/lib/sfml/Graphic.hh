#ifndef GRAPHIC_HH_
# define GRAPHIC_HH_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "graphics.hh"

#define WINNAME "Nibbler"

class Graphic : public IGraphic
{
public:
  Graphic();
  ~Graphic();
  void			Init(int keyboard, const SnakeGame::GameData& data);
  void			Destroy();
  SnakeGame::Event	GetEvent();
  void			Display(const SnakeGame::GameData &data);
private:
  sf::RenderWindow		*_win;
  int				_keyboard;
  std::map<sf::Keyboard::Key, int>	_keymap;
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Sprite> sprites;
};

#endif /* !GRAPHIC_HH_ */
