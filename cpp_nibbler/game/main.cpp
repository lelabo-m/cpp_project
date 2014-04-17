#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "gameexception.hpp"
#include "nibbler.hh"

int	usage(int ac, char **av)
{
  std::cout << "usage [" << (ac ? av[0] : "nibbler") << "] : "
	    << "sizex sizey libXXX.so" << std::endl;
  return (1);
}

int	parse_size(std::string param)
{
  std::stringstream	ss;
  char			*str;
  unsigned int		val;

  str = const_cast<char *>(param.c_str());
  for (unsigned int i = 0; i < param.size(); ++i)
    {
      if (!(str[i] >= '0' && str[i] <= '9'))
	return (-1);
    }
  ss << str;
  ss >> val;
  return ((int)(val));
}

int	main(int ac, char **av, char **env)
{
  if (ac - 4)
    return (usage(ac, av));
  if (env == NULL || *env == NULL || env[0] == 0 || getenv("SHELL") == NULL)
    {
      std::cout << "No env!" << std::endl;
      return (1);
    }
  srand(time(NULL));
  try
    {
      int	x = parse_size(av[1]);
      int	y = parse_size(av[2]);

      if ((x < 15 || y < 15) || (x > 192 || x > 108))
	{
	  std::cerr << "Bad size parameter." << std::endl;
	  return (1);
	}
      SnakeGame::Nibbler	game(av[3], x, y, 0);
      game.Launch();
    }
  catch (SnakeGame::GraphicException &e)
    {
      std::cout << e.what() << std::endl;
      return (1);
    }
  return (0);
}
