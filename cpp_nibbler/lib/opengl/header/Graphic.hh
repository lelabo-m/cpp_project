#ifndef GRAPHIC_HH
#define GRAPHIC_HH

#include        <GL/gl.h>
#include        <GL/glut.h>
#include        <SDL/SDL.h>
#include	<string>
#include	<iostream>
#include	<map>
#include	"graphics.hh"
#include	"nibbler.hh"

class Graphic : public IGraphic
{
 private:

  static SnakeGame::GameData	*_data;
  static SnakeGame::Event	*_gameEv;

  static GLuint		_displayList;
  static GLuint		_displayListWall;
  static GLuint		_displayListSnake;
  static GLuint		_displayListApple;
  static GLuint		_displayListHead;

  static int		_w;
  static int		_h;

  static std::map<unsigned int,unsigned int> map_keys;
  float			_angle;
  int			_k;

 public:

  Graphic();
  virtual ~Graphic();

  virtual void		Init(int, const SnakeGame::GameData &data);
  void			Destroy();
  virtual void		Display(const SnakeGame::GameData &data);
  SnakeGame::Event	GetEvent();

  void		initRendering();
  static void	drawScene();
  static void	handleResize(int, int);
  static void	handleKeypress(unsigned char, int, int);
  static void	handleArrowpress(int, int, int);
  void		drawCube(float, float, float, float);

};

#define	WINX	800
#define WINY	600

#endif  /* GRAPHIC_HH */

