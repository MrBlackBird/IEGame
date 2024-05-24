#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap {
private:
  std::vector<std::vector<Tile *>> tiles_;

public:
  TileMap();
  ~TileMap();

  // functions
  void add_tile(unsigned xCord, unsigned yCord);
  void remove_tile(unsigned xCord, unsigned yCord);
  void update();
  void render();
};
