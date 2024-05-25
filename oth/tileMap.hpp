#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class TileMap {
private:
  std::vector<std::vector<Tile *>> tiles_;
  sf::Texture *tileSheet_;
  unsigned tileSize_;

public:
  TileMap();
  TileMap(unsigned witdth, unsigned height, sf::Texture *tileSheet,
          unsigned tileSize);
  ~TileMap();

  // functions
  void add_tile(unsigned xCord, unsigned yCord);
  void remove_tile(unsigned xCord, unsigned yCord);
  void update();
  void render(sf::RenderTarget &target);
};
