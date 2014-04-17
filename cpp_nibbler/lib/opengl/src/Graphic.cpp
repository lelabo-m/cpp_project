#include <string>
#include <iostream>
#include <GL/freeglut.h>
#include "Graphic.hh"
#include "nibbler.hh"
#include "event.hh"

GLuint Graphic::_displayList = 0;
GLuint Graphic::_displayListWall = 0;
GLuint Graphic::_displayListSnake = 0;
GLuint Graphic::_displayListApple = 0;
GLuint Graphic::_displayListHead = 0;

SnakeGame::GameData*	Graphic::_data = 0;
SnakeGame::Event*	Graphic::_gameEv = 0;

std::map<unsigned int,unsigned int> Graphic::map_keys;
Graphic::Graphic()
{
  map_keys[GLUT_KEY_UP] = (unsigned int)UP;
  map_keys[GLUT_KEY_DOWN] = (unsigned int)DOWN;
  map_keys[GLUT_KEY_RIGHT] = (unsigned int)RIGHT;
  map_keys[GLUT_KEY_LEFT] = (unsigned int)LEFT;
  map_keys[75] = (unsigned int)SPACE;
  map_keys[27] = (unsigned int)ESC;
  map_keys[16] = (unsigned int)PLAY_PAUSE;
  map_keys[13] = (unsigned int)MUSIC;
  map_keys[67] = (unsigned int)ENTER;
  map_keys[63] = (unsigned int)BACKSPACE;
}

Graphic::~Graphic()
{
}

void	Graphic::Init(int, const SnakeGame::GameData &data)
{
  int	fakeAC = 1;
  void	(*ptrHandleResize)(int, int);
  void	(*ptrHandleKeyPress)(unsigned char, int, int);
  void	(*ptrHandleArrowPress)(int, int, int);
  void	(*ptrDrawScene)(void);

  glutInit(&fakeAC, NULL);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINX, WINY);
  glutCreateWindow("Nibbler");
  initRendering();

  Graphic::_data = &const_cast<SnakeGame::GameData&>(data);


  ptrDrawScene = Graphic::drawScene;
  ptrHandleResize = Graphic::handleResize;
  ptrHandleKeyPress = Graphic::handleKeypress;
  ptrHandleArrowPress = Graphic::handleArrowpress;

  glutDisplayFunc((*ptrDrawScene));
  glutIdleFunc((*ptrDrawScene));
  glutReshapeFunc((*ptrHandleResize));
  glutKeyboardFunc((*ptrHandleKeyPress));
  glutSpecialFunc((*ptrHandleArrowPress));

  _gameEv = new SnakeGame::Event();

}

void    Graphic::initRendering()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.0f, 0.197f, 0.205f, 1.0f);
  Graphic::_displayList = glGenLists(1);
  glNewList(Graphic::_displayList, GL_COMPILE);
  drawCube(0.084f, 0.139f, 0.084f, 0.3f);
  glEndList();
  Graphic::_displayListWall = glGenLists(2);
  glNewList(Graphic::_displayListWall, GL_COMPILE);
  drawCube(0.4f, 0.3f, 0.2f, 0.7f);
  glEndList();
  Graphic::_displayListSnake = glGenLists(3);
  glNewList(Graphic::_displayListSnake, GL_COMPILE);
  drawCube(0.112f, 0.128f, 0.144f, 0.7f);
  glEndList();
  Graphic::_displayListApple = glGenLists(4);
  glNewList(Graphic::_displayListApple, GL_COMPILE);
  drawCube(1.0f, 0.0f, 0.0f, 0.7f);
  glEndList();
  Graphic::_displayListHead = glGenLists(5);
  glNewList(Graphic::_displayListHead, GL_COMPILE);
  drawCube(0.205f, 0.181f, 0.205f, 0.7f);
  glEndList();
}

void	Graphic::drawCube(const float r, const float g, const float b, const float x)
{
  glBegin(GL_QUADS);
  glColor3f(0.05f, 0.05f, 0.05f);
  glTranslatef(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.00f, 0.0f, 0.0f);
  glVertex3f(1.0f, x, 0.0f);
  glVertex3f(0.0f, x, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.05f, 0.05f, 0.05f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  glVertex3f(0.0f, x, -1.0f);
  glVertex3f(0.0f, x, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.05f, 0.05f, 0.05f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, -1.0f);
  glVertex3f(1.0f, x, -1.0f);
  glVertex3f(1.0f, x, 0.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.05f, 0.05f, 0.05f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  glVertex3f(1.00f, 0.0f, -1.0f);
  glVertex3f(1.0f, x, -1.0f);
  glVertex3f(0.0f, x, -1.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.05f, 0.05f, 0.05f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.00f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, -1.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(r, g, b);
  glVertex3f(0.0f, x, 0.0f);
  glVertex3f(1.00f, x, 0.0f);
  glVertex3f(1.0f, x, -1.0f);
  glVertex3f(0.0f, x, -1.0f);
  glEnd();
}

void	Graphic::drawScene()
{
  float	i = 0.0;
  float	j = 0.0;
  float	x = 0;
  float	y = 0;
  int	lenght = Graphic::_data->_map->GetLength();
  int	width = Graphic::_data->_map->GetWidth();
  int   size = Graphic::_data->_map->GetLength() * _data->_map->GetWidth();
  bool	isSnake = false;
  std::list<SnakeGame::SnakeBody *>::iterator it = _data->_player->GetBody().begin();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(0.0, 0.0f, 10.0f, 0.0f);
  glTranslatef(-6*1.0, 0.0, 6*1.0);
  while (j < lenght)
    {
      i = 0.0;
      while (i < width)
        {
          glPushMatrix();
	  isSnake = false;
      	  if ((Graphic::_data->_map->GetMapCell(j,i) == SnakeGame::WALL) && (i != 0 || j != -1))
            {
              glTranslatef(-lenght+j, 0.0, -width+i);
              glCallList(Graphic::_displayListWall);
            }
      	  else if ((Graphic::_data->_map->GetMapCell(j,i) == SnakeGame::APPLE) && (i != 0 || j != -1))
            {
              glTranslatef(-lenght+j, 0.0, -width+i);
              glCallList(Graphic::_displayListApple);
            }
	  else
	    {
	      it = _data->_player->GetBody().begin();
	      while (it != _data->_player->GetBody().end())
		{
		  x = (*it)->x;
		  y = (*it)->y;
		  if (j == x && i == y)
		    {
		      glTranslatef(-lenght+j, 0.3, -width+i);
		      if (it == _data->_player->GetBody().begin())
			glCallList(Graphic::_displayListHead);
		      else
			glCallList(Graphic::_displayListSnake);
		      isSnake = true;
		    }
		  it++;
		}
	      if (isSnake == false)
		{
		  glTranslatef(-lenght+j, 0.0, -width+i);
		  glCallList(Graphic::_displayList);
		}
	    }
	  glPopMatrix();
      	  i += 1.0;
      	}
      j += 1.0;
    }
  glutSwapBuffers();
}

void    Graphic::handleResize(const int w, const int h)
{
  float	x = 0.0;
  float	y = 0.0;
  int	lenght = Graphic::_data->_map->GetLength();
  int	width = Graphic::_data->_map->GetWidth();

  int	i = 0;
  for (std::list<SnakeGame::SnakeBody *>::iterator it = _data->_player->GetBody().begin();
       it != _data->_player->GetBody().end() ; ++it)
    {
      if (i == 0)
	{
	  x = (*it)->x;
	  y = (*it)->y;
	  i = 1;
	}
    }
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 200);
  gluLookAt(0, 30.0, 15.0f, -lenght+x, 0.0f, -width+y, 0.0f, 1.0f, 0.0f);
}

void    Graphic::handleKeypress(const unsigned char key, const int , const int )
{
  _gameEv->type = SnakeGame::EMOVE;
  _gameEv->value = map_keys[key];
}

void    Graphic::handleArrowpress(const int key, const int , const int )
{
  _gameEv->type = SnakeGame::EMOVE;
  _gameEv->value = map_keys[key];
}

void    Graphic::Display(const SnakeGame::GameData &data)
{

  _gameEv->type = SnakeGame::ENONE;
  _gameEv->value = 0;
}

void	Graphic::Destroy()
{

}

SnakeGame::Event Graphic::GetEvent()
{
  handleResize(WINX, WINY);
  drawScene();
  glutMainLoopEvent();
  return (*_gameEv);
}

extern "C" IGraphic *entry_point()
{
  return (new Graphic());
}
