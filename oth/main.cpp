// g++ main.cpp game.cpp player.cpp enemy.cpp healthBar.cpp backgr.cpp -o
// gametest -lsfml-graphics -lsfml-window -lsfml-system

#include "game.hpp"
#include <cstdlib>
#include <ctime>
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
