#ifndef GRAPHIC_HH_
# define GRAPHIC_HH_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#define WINNAME "Nibbler"

enum MoveValue {NONE, UP, DOWN, RIGHT, LEFT, SPACE, ESC, PLAY_PAUSE, MUSIC, ENTER, BACKSPACE};

class Graphic
{
public:
  Graphic();
  ~Graphic();
  void			Init();
  void			Destroy();
  int			GetEvent();
  void			Display();
private:
  sf::RenderWindow		*_win;
  std::map<sf::Keyboard::Key, int>	_keymap;
  std::map<std::string, sf::Texture> textures;
  std::map<std::string, sf::Sprite> sprites;
  unsigned int	l_green;
  unsigned int	l_blue;
  unsigned int	l_red;
  unsigned int	l_star;
  bool		green_activate;
  bool		blue_activate;
  bool		red_activate;
  bool		star_activate;
  std::string	nb_1;
  std::string	nb_2;
  sf::Font	font;
};

#endif /* !GRAPHIC_HH_ */
