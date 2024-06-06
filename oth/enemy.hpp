#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "gameObject.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

enum ENEMY_ANIM_STATES { IDLE_E = 0, LEFT_E, RIGHT_E, ATTACK_E, DEATH_E };

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
  float acceleration_;
  float drag_;
  float gravity_;
  float maxGravitationalVelocity_;

  // FIX: core
  int damage_;
  int health_;
  sf::Vector2f currentPosition_;
  float distanceToPlayer_;

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
  const sf::Vector2f get_position() const;
  const sf::FloatRect get_global_bounds() const;

  // modifiers
  void set_position(const float xCord, const float yCord);

  // functions
  void move(const float xDir, const float yDir, float deltaTime);
  void chase_player(float deltaTime);
  void movement(Player &player, float deltaTime);
  void animations();
  void reset_velocity_y();
  void update_distance_to_player(float playerXPosition);
  void update_physics(float deltaTime);
  void update(float playerXPosition, float deltaTime);
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};

#endif // ENEMY_HPP
