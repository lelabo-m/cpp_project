#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <exception>
#include "Graphic.hh"

extern char **environ;

int		main()
{
  Graphic inter;
  int	i;

  if (environ == NULL || *environ == NULL || environ[0] == 0 || getenv("SHELL") == NULL)
    {
      std::cout << "No env!" << std::endl;
      return (1);
    }
  srand(time(NULL));
  try
    {
      inter.Init();
      inter.Display();
      while ((i = inter.GetEvent()) < 0)
	{
	  inter.Display();
	}
      if (i == 1)
	{
	  i = rand() % 3 + 2;
	}
      if (i == 2)
	system("./nibbler 37 21 lib/libso/lib_nibbler_allegro.so");
      else if (i == 3)
	system("./nibbler 37 21 lib/libso/lib_nibbler_opengl.so");
      else if (i == 4)
	system("./nibbler 37 21 lib/libso/lib_nibbler_sfml.so");
      inter.Destroy();
    }
  catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
}
