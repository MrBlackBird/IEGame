#include "object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Enemy : public Object {
private:
  sf::Vector2f defaultPosition_ = sf::Vector2f(50.0, 300.0);
  sf::Vector2f size_ = sf::Vector2f(15.0, 30.0);
  sf::Texture enemyTexture_;
  sf::Sprite enemySprite_;

public:
  Enemy() {
    enemyTexture_.loadFromFile("guy.png");
    enemySprite_.setTexture(enemyTexture_);
    enemySprite_.setPosition(defaultPosition_);
  }

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(enemySprite_, states);
  }

  void movement(sf::Time frameTime, sf::Vector2f &velocityXY,
                const std::vector<sf::FloatRect> &wallsBounds,
                sf::Window &windowBounds) {

    // calculate players' new position
    sf::Vector2f updatedPosition =
        enemySprite_.getPosition() + velocityXY * frameTime.asSeconds();

    // get player bounds & adjust them to fit visually
    sf::FloatRect enemyBounds(updatedPosition, size_);
    enemyBounds.top += 10;
    enemyBounds.left += 10;
    enemyBounds.width += 10;
    enemyBounds.height += 30;

    // check for collisions with walls
    bool collision = false;
    for (const sf::FloatRect &wall : wallsBounds) {
      if (enemyBounds.intersects(wall)) {
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
        enemySprite_.setPosition(updatedPosition);
      }
    }
  }
};
