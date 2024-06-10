#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

enum PLAYER_ANIM_STATES { IDLE = 0, LEFT, RIGHT, JUMP, FALL, ROLL, ATTACK };

class Player : public Object {
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
  sf::Vector2f currentPosition_;

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
  const sf::FloatRect get_global_bounds_for_platforms() const;
  const sf::Vector2f get_velocity() const;
  const bool get_is_facing_left() const;
  const bool get_is_dead() const;

  // modifiers
  void set_position(const float xCord, const float yCord);
  void reset_velocity_y();
  void set_is_grounded(bool grounded);
  void take_damage();
  bool isDead_;

  // functions
  void reset_animation_timer();
  void move(const float xDir, const float yDir, float deltaTime);
  void movement(float deltaTime);
  void animations();
  void update_physics(float deltaTime);
  bool get_if_attack_state();
  void check_death();
  void update(float deltaTime);
  // void render(sf::RenderTarget &target);
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};

#endif // PLAYER_HPP
