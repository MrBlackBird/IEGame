#ifndef PLAYER_HPP
#define PLAYER_HPP

// FIX: add poymorphism
// #include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

enum PLAYER_ANIM_STATES { IDLE = 0, LEFT, RIGHT, JUMP, FALL, ROLL, ATTACK };

class Player {
private:
  sf::Sprite sprite_;
  sf::Texture IDLEtexture_;
  sf::Texture RUNtexture_;
  sf::Texture JUMPtexture_;
  sf::Texture FALLtexture_;
  sf::Texture ROLLtexture_;
  sf::Texture ATTACKtexture_;

  // FIX: animation
  sf::IntRect currentFrame_;
  sf::Clock animationTimer_;
  short animationState_;

  // FIX: physics
  sf::Vector2f velocity_;
  float maxVelocity_;
  float minVelocity_;
  float acceleration_;
  float drag_;

  // FIX: core

  void init_variables();
  void init_texture();
  void init_sprite();
  void init_animations();
  void init_physics();

public:
  // constructor and destructor
  Player();
  virtual ~Player();

  // functions
  // void draw(sf::RenderTarget &target, sf::RenderStates states) const
  // override;
  void move(const float xDir, const float yDir);
  void movement();
  void animations();
  void update_physics();
  void update();
  void render(sf::RenderTarget &target);
};

#endif // PLAYER_HPP
