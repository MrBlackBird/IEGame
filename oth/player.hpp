#ifndef PLAYER_HPP
#define PLAYER_HPP

// FIX: add poymorphism
#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

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
  bool animationSwitch_;
  bool facingLeft_;
  bool isGrounded_;
  float groundLevel_;

  // FIX: physics
  sf::Vector2f velocity_;
  float maxVelocity_;
  float minVelocity_;
  float acceleration_;
  float drag_;
  float gravity_;
  float maxGravitationalVelocity_;

  // FIX: core
  int damage_;
  int health_;

  void init_variables();
  void init_texture();
  void init_sprite();
  void init_animations();
  void init_physics();
  void init_core();

public:
  // constructor and destructor
  Player();
  virtual ~Player();

  // getters
  const bool get_animation_switch();
  const sf::Vector2f get_position() const;
  const sf::FloatRect get_global_bounds() const;

  // modifiers
  void set_position(const float xCord, const float yCord);
  void reset_velocity_y();

  // functions
  void reset_animation_timer();
  void move(const float xDir, const float yDir, float deltaTime);
  void movement(float deltaTime);
  void animations();
  void update_physics(float deltaTime);
  void update(float deltaTime);
  void render(sf::RenderTarget &target);
  // virtual void draw(sf::RenderTarget &target,
  //                   sf::RenderStates states) const override;
};

#endif // PLAYER_HPP
