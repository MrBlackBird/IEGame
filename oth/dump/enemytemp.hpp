#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "gameObject.hpp"
#include <SFML/Graphics.hpp>

enum ENEMY_ANIM_STATES { IDLE = 0, LEFT, RIGHT, ATTACK, DEATH };

class Enemy : public Object {
private:
  sf::Sprite sprite_;
  sf::Texture IDLEtexture_;
  sf::Texture RUNtexture_;
  sf::Texture ATTACKtexture_;
  sf::Texture DEATHtexture_;

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
  Enemy();
  virtual ~Enemy();

  // getters
  const bool get_animation_switch();
  const sf::Vector2f get_position() const;
  const sf::FloatRect get_global_bounds() const;

  // modifiers
  void set_position(const float xCord, const float yCord);

  // functions
  void reset_animation_timer();
  void move(const float xDir, const float yDir, float deltaTime);
  void movement(float deltaTime);
  void animations();
  void update_physics(float deltaTime);
  void update(float deltaTime);
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};

#endif // ENEMY_HPP
