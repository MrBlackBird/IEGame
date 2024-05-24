#ifndef GAME_HPP
#define GAME_HPP

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

  void init_window();
  void init_player();

public:
  // constructor & destructor
  Game();
  virtual ~Game();

  // functions
  const sf::RenderWindow &get_window() const;
  void update();
  void render();
  void update_player();
  void render_player();
};

#endif // GAME_HPP
