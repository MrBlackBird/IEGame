#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>

int main() {

  srand(static_cast<unsigned>(time(0)));
  Game game;

  while (game.get_window().isOpen()) {
    game.update();
    game.render();
  }

  return 0;
}
