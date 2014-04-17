#ifndef GRAPHICS_H_
# define GRAPHICS_H_

namespace SnakeGame
{
  class GameData;

  struct Event;
}

enum MoveValue {NONE, UP, DOWN, RIGHT, LEFT, SPACE, ESC, PLAY_PAUSE, MUSIC, ENTER, BACKSPACE};

class IGraphic
{
public:
  virtual ~IGraphic(){};
  virtual void	Init(int KeyBoard, const SnakeGame::GameData &data) = 0;
  virtual void	Destroy() = 0;
  virtual SnakeGame::Event	GetEvent() = 0;
  virtual void	Display(const SnakeGame::GameData &data) = 0;
};

#endif /* !GRAPHICS_H_ */
