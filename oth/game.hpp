#ifndef GAME_HPP
#define GAME_HPP

#include "backgr.hpp"
#include "enemy.hpp"
#include "healthBar.hpp"
#include "platforms.hpp"
#include "player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Game {
private:
  // NOTE: objects
  Player *player_;
  BackGround *backGround_;
  HealthBar *healthBar_;
  std::vector<Enemy *> enemies_;
  Enemy *enemy1_;
  Enemy *enemy2_;
  Enemy *enemy3_;
  Platform *platforms_;
  std::vector<std::unique_ptr<Object>> objects_;

  // NOTE: core
  sf::RenderWindow window_;
  sf::Event event_;
  sf::Clock clock_;
  float deltaTime_;
  int score_;

  // NOTE: useful variables
  float playerXPosition_; // for easy enemie movement
  float playerXenemyDistance_;

  void init_window();
  void init_player();
  void init_background();
  void init_health_bar();
  void init_enemy();
  void init_enemy_two();
  void init_enemy_three();
  void init_platforms();

public:
  // constructor & destructor
  Game();
  virtual ~Game();

  // getters
  bool get_if_player_dead();
  int get_score();

  // functions
  const sf::RenderWindow &get_window() const;
  void update();
  void render();
  void update_player(float deltaTime_);
  void update_enemy(float deltaTime_);
  void update_platforms();
  void render_objects();
  void updateCollision();
  void update_score();
  void player_killed(bool killed);
  void game_over();
};

#endif // GAME_HPP
