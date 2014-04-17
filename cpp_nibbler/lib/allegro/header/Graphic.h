#ifndef GRAPHIC_H
#define	GRAPHIC_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <map>
#include "graphics.hh"

class Graphic : public IGraphic
{
public:
  Graphic();
  ~Graphic();
  void Init(int keyboard, const SnakeGame::GameData &data);
  void Destroy();
  SnakeGame::Event GetEvent();
  void Display(const SnakeGame::GameData &data);
private:
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_EVENT ev;
  ALLEGRO_TIMEOUT timeout;
  std::map<unsigned int,unsigned int> map_keys;
  ALLEGRO_BITMAP *bmp;
  ALLEGRO_BITMAP *bmp_head;
  ALLEGRO_BITMAP *bmp_carre;
  ALLEGRO_BITMAP *bmp_wall;
};

#endif	/* GRAPHIC_H */
