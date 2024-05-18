#include "GameObject/player/player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <vector>

void fill_gameObjects(std::vector<std::unique_ptr<Object>> &goVec,
                      std::vector<sf::FloatRect> &wallsBounds) {

  // create & setup game objects (background, player and 3 walls)
  //  auto grass = make_unique<Environment>();
  //  grass->setTexture("grass.png");
  //  grass->setSize(sf::Vector2f(800.0, 600.0));
  //  grass->setPosition(sf::Vector2f(0.0, 0.0));
  //  goVec.emplace_back(std::move(grass));

  auto player = std::make_unique<Player>();
  goVec.emplace_back(std::move(player));
}

int main() {

  // some neccessary global variables
  sf::Vector2f velocity(0.f, 0.f);
  std::vector<sf::FloatRect> wallsBounds;

  sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
  window.setFramerateLimit(144);

  // store game objects
  std::vector<std::unique_ptr<Object>> gameObjects;
  fill_gameObjects(gameObjects, wallsBounds);

  // handle time
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Time frameTime = clock.restart();

    sf::Event event;
    while (window.pollEvent(event)) {

      // close window
      if (event.type == sf::Event::Closed) {
        window.close();

        // handle velocity changes after keypress
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
          velocity.x = -500.0;
        } else if (event.key.code == sf::Keyboard::Right) {
          velocity.x = 500.0;
        } else if (event.key.code == sf::Keyboard::Up) {
          velocity.y = -500.0;
        } else if (event.key.code == sf::Keyboard::Down) {
          velocity.y = 500.0;
        }
      } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::Right) {
          velocity.x = 0.0;
        } else if (event.key.code == sf::Keyboard::Up ||
                   event.key.code == sf::Keyboard::Down) {
          velocity.y = 0.0;
        }
      }
    }

    // get the player from the vector and enable movement
    for (auto &obj : gameObjects) {
      Player *playerTemp = dynamic_cast<Player *>(obj.get());
      if (playerTemp) {
        playerTemp->movement(frameTime, velocity, wallsBounds, window);
        break;
      }
    }

    // clear window
    window.clear();

    // draw the objects
    for (auto &obj : gameObjects) {
      obj->draw(window, sf::RenderStates::Default);
    }

    // show frame
    window.display();
  }

  return 0;
}
