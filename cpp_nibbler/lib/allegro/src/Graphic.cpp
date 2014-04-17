#include <iostream>
#include "nibbler.hh"
#include "Graphic.h"
#include "event.hh"

Graphic::Graphic()
{
  map_keys[84] = (unsigned int)UP;
  map_keys[85] = (unsigned int)DOWN;
  map_keys[83] = (unsigned int)RIGHT;
  map_keys[82] = (unsigned int)LEFT;
  map_keys[75] = (unsigned int)SPACE;
  map_keys[59] = (unsigned int)ESC;
  map_keys[16] = (unsigned int)PLAY_PAUSE;
  map_keys[13] = (unsigned int)MUSIC;
  map_keys[67] = (unsigned int)ENTER;
  map_keys[63] = (unsigned int)BACKSPACE;
}

Graphic::~Graphic() {
}

void Graphic::Init(int keyboard, const SnakeGame::GameData &data)
{
  if (!al_init())
    {
      al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  int	coeff = 20;
  display = al_create_display(data._map->GetLength() * coeff, data._map->GetWidth() * coeff);

  if (!display)
    {
      al_show_native_message_box(display, "Sample title", "Display Settings", "Display Windows error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  if (!al_init_primitives_addon())
    {
      al_show_native_message_box(display, "Sample title", "Display Settings", "Display Windows error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  if (!al_init_image_addon())
    {
      al_show_native_message_box(display, "Sample title", "Display Settings", "Display Windows error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  bmp = al_load_bitmap("./imgs/tron_snake.png");
  bmp_carre = al_load_bitmap("./imgs/tron_carre.png");
  bmp_head = al_load_bitmap("./imgs/tron_head.png");
  bmp_wall = al_load_bitmap("./imgs/tron_bout.png");

  event_queue = al_create_event_queue();

  if (!event_queue)
    {
      al_show_native_message_box(display, "Sample title", "Display Settings", "Event queue error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  if(!al_install_keyboard())
    {
      al_show_native_message_box(display, "Sample title", "Display Settings", "Install keyboard error", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void Graphic::Display(const SnakeGame::GameData &data)
{
  int	size = data._map->GetLength() * data._map->GetWidth();
  int	coeff = 20;
  int	coords[4];

  al_clear_to_color(al_map_rgb(5, 5, 5));
  for (int i = 0; i < size; i+=1)
    {
      coords[0] = (i / data._map->GetWidth())*coeff;
      coords[1] = (i % data._map->GetWidth())*coeff;
      coords[2] = (i / data._map->GetWidth() + 1)*coeff;
      coords[3] = (i % data._map->GetWidth() + 1)*coeff;
      if (data._map->GetMapCell(i) == SnakeGame::WALL)
	al_draw_scaled_bitmap(bmp_wall, 0.0, 0.0, 400.0, 400.0, coords[0], coords[1], coeff * 1.0, coeff * 1.0, 0);
      else if (data._map->GetMapCell(i) == SnakeGame::APPLE)
	al_draw_filled_rectangle(coords[0], coords[1], coords[2], coords[3], al_map_rgb(255, 180, 34));
      else
	al_draw_scaled_bitmap(bmp_carre, 0.0, 0.0, 200.0, 200.0, coords[0], coords[1], coeff * 1.0, coeff * 1.0, 0);
    }
  for(std::list<SnakeGame::SnakeBody *>::iterator it = data._player->GetBody().begin(); it != data._player->GetBody().end(); ++it)
    {
      coords[0] = (*it)->x*coeff;
      coords[1] = (*it)->y*coeff;
      coords[2] = ((*it)->x+1)*coeff;
      coords[3] = ((*it)->y+1)*coeff;
      if (it == data._player->GetBody().begin())
	al_draw_scaled_bitmap(bmp_head, 0, 0, 200, 200, coords[0], coords[1], coeff, coeff, 0);
      else
	al_draw_scaled_bitmap(bmp, 0, 0, 300, 300, coords[0], coords[1], coeff, coeff, 0);
    }
  al_flip_display();
}

SnakeGame::Event Graphic::GetEvent()
{
  SnakeGame::Event		gameEv;

  gameEv.type = (SnakeGame::ENONE);
  gameEv.value = 0;
  al_init_timeout(&timeout, 0.1);
  bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
  if (get_event && ev.type == 12)
    {
      gameEv.type = SnakeGame::EMOVE;
      gameEv.value = map_keys[ev.keyboard.keycode];
    }
  return (gameEv);
}

void Graphic::Destroy()
{
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
}

extern "C" IGraphic *entry_point()
{
  return (new Graphic());
}
