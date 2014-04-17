#ifndef MAP_HH_
# define MAP_HH_

#include <string>
#include <vector>

#define START_FOOD 3
#define START_WALL 10

namespace SnakeGame
{
  enum MapCell {VOID, WALL, APPLE};

  class Map
  {
  public:
    Map(unsigned int length, unsigned int width, unsigned int mode);
    Map(const std::string& file);
    ~Map();
    unsigned int	GetLength() const;
    unsigned int	GetWidth() const;
    void	GenMap();
    void	GenRandMap();
    void	SetMapCell(unsigned int x, unsigned int y, const MapCell value);
    void	SetRandMapCell(MapCell value);
    MapCell	GetMapCell(unsigned int x, unsigned int y) const;
    MapCell	GetMapCell(unsigned int pos) const;
    void	GetRandPosition(unsigned int *x, unsigned int *y);
    void	Dump() const;
  private:
    std::vector<MapCell>	_map;
    unsigned int	_length;
    unsigned int	_width;
  };
}

#endif /* !MAP_HH_ */
