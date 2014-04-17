#ifndef SNAKE_HH_
# define SNAKE_HH_

#include <list>

#define SNAKE_SPEED 100

namespace SnakeGame
{
  class GameData;

  struct SnakeBody
  {
    float	x;
    float	y;
    int		statut;
  };

  class Snake
  {
  public:
    Snake(int time = 0, int id = 0, int speed = 500);
    ~Snake();
    static void	SnakeDestroyBody(SnakeBody *);
    bool	Updateable(int);
    void	Update(int);
    int		GetSpeed() const;
    int		GetId() const;
    int		GetDirection() const;
    std::list<SnakeBody *>	&GetBody();
    void	SetSpeed(int);
    void	SetId(int);
    void	AddBody(float, float, int);
    void	PlaceBody(GameData&);
    bool	BodyBroken();
  private:
    int				_id;
    int				_speed;
    int				_lastupdate;
    int				_direction;
    std::list<SnakeBody *>	_body;
    // Event Method
  public:
    void	EventClose(GameData&);
    void	EventPauseON(GameData&);
    void	EventPauseOFF(GameData&);
    void	MoveForward(GameData&);
    void	MoveRight(GameData&);
    void	MoveLeft(GameData&);
    void	EatApple(GameData&);
    void	PopWall(GameData&);
  };
}

#endif /* !SNAKE_HH_ */

