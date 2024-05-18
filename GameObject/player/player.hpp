#include "object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Player : public Object {
private:
  sf::Vector2f defaultPosition_ = sf::Vector2f(50.0, 300.0);
  sf::Vector2f size_ = sf::Vector2f(15.0, 30.0);
  sf::Texture playerTexture_;
  sf::Sprite playerSprite_;

public:
  Player() {
    playerTexture_.loadFromFile("guy.png");
    playerSprite_.setTexture(playerTexture_);
    playerSprite_.setPosition(defaultPosition_);
  }

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(playerSprite_, states);
  }

  void movement(sf::Time frameTime, sf::Vector2f &velocityXY,
                const std::vector<sf::FloatRect> &wallsBounds,
                sf::Window &windowBounds) {

    // calculate players' new position
    sf::Vector2f updatedPosition =
        playerSprite_.getPosition() + velocityXY * frameTime.asSeconds();

    // get player bounds & adjust them to fit visually
    sf::FloatRect playerBounds(updatedPosition, size_);
    playerBounds.top += 10;
    playerBounds.left += 10;
    playerBounds.width += 10;
    playerBounds.height += 30;

    // check for collisions with walls
    bool collision = false;
    for (const sf::FloatRect &wall : wallsBounds) {
      if (playerBounds.intersects(wall)) {
        collision = true;
        break;
      }
    }

    // check for window bounds & adjust them to fit visually
    if (updatedPosition.x >= 0 && updatedPosition.y >= 0 &&
        updatedPosition.x + size_.x <= windowBounds.getSize().x - 25 &&
        updatedPosition.y + size_.y <= windowBounds.getSize().y - 35) {

      // update player's position if no collisions are detected
      if (!collision) {
        playerSprite_.setPosition(updatedPosition);
      }
    }
  }
};
