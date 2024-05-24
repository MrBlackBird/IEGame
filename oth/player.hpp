#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public Object {
private:
  sf::Texture texture_;

  // FIX: movement

  // FIX: animation

  // FIX: core

  void init_texture();
  void init_sprite();

public:
  Player();
  virtual ~Player();

  void update();
  void render(sf::RenderTarget &target);
  // void draw(sf::RenderTarget &target, sf::RenderStates states) const
  // override;
};

#endif // PLAYER_HPP
