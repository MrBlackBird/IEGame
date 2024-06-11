#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>

int main() {

  srand(static_cast<unsigned>(time(0)));
  Game game;

  // game loop
  while (game.get_window().isOpen()) {
    // if (game.get_if_player_dead() == false) {
    game.update();
    game.render();
    // } else {
    // game.game_over();
    //}
  }
  game.update_score();
  std::cout << "GAME OVER" << std::endl;
  std::cout << "Score: " << game.get_score() << std::endl;

  return 0;
}
