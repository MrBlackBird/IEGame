#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tile {
private:
  sf::Sprite sprite_;
  bool damaging_;

public:
  Tile(sf::Texture *&texture, sf::IntRect textureRect,
       const bool damaging = false);
  virtual ~Tile();

  // functions
  const sf::FloatRect get_global_bounds() const;
  void update();
  void render(sf::RenderTarget &target);
};

#endif // TILE_HPP
