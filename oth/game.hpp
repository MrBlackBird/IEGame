#ifndef GAME_HPP
#define GAME_HPP

// #include "backgr.hpp"
#include "player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>

class Game {
private:
  sf::RenderWindow window_;
  sf::Event event_;
  std::unique_ptr<Player> player_;
  // std::unique_ptr<BackGround> backGround_;
  // std::vector<std::unique_ptr<Object>> objects_;

  void init_window();
  void init_player();
  // void init_background();

public:
  // constructor & destructor
  Game();
  virtual ~Game();

  // functions
  const sf::RenderWindow &get_window() const;
  void update();
  void render();
  void update_player();
  void render_objects();
  void updateCollision();
};

#endif // GAME_HPP
