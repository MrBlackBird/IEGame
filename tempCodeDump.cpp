#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <vector>

// for easy handling of different animation types
enum class AnimationType { Idle, Walking, Attacking, Rolling };

// setup for polymorphism
class Object : public sf::Drawable {
public:
  virtual void update(sf::Time frameTime) = 0;
  virtual ~Object() = default;
};

// an intermidiate class for storing most of the common variables/functions
class AnimatedObject : public Object {
protected:
  sf::Sprite sprite_;
  float timeSinceLastFrame_;
  int currentFrame_;
  std::map<AnimationType, std::vector<sf::IntRect>> animFrames_;
  std::map<AnimationType, int> animFrameRates_;
  AnimationType currentState_;

public:
  // constructor
  AnimatedObject()
      : timeSinceLastFrame_(0), currentFrame_(0),
        currentState_(AnimationType::Idle) {}

  // adding frames to the vector of animation frames
  void addAnimationFrame(AnimationType state, const sf::IntRect &frame) {
    animFrames_[state].emplace_back(frame);
  }

  // set framerate of an animation
  void setFrameRate(AnimationType state, int frameRate) {
    animFrameRates_[state] = frameRate;
  }

  // set animaion state
  void setState(AnimationType state) {
    if (state != currentState_) {
      currentState_ = state;
      currentFrame_ = 0;
      timeSinceLastFrame_ = 0;
    }
  }

  // update current animation
  void updateAnimation(sf::Time elapsed) {
    timeSinceLastFrame_ += elapsed.asSeconds();
    int frameRate = animFrameRates_[currentState_];
    if (timeSinceLastFrame_ > (1.0f / frameRate)) {
      currentFrame_ = (currentFrame_ + 1) % animFrames_[currentState_].size();
      sprite_.setTextureRect(animFrames_[currentState_][currentFrame_]);
      timeSinceLastFrame_ = 0;
    }
  }

  // polymorphic draw function
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(sprite_, states);
  }

  // apply the updated animation frame
  virtual void update(sf::Time frameTime) override {
    updateAnimation(frameTime);
  }
};

// the main player/character class
class Player : public AnimatedObject {
private:
  sf::Vector2f defaultPosition_;
  sf::Vector2f size_;

public:
  // constructor
  Player(const sf::Texture &texture, int frameRate)
      : AnimatedObject(), defaultPosition_(50.0f, 300.0f), size_(15.0f, 30.0f) {
    sprite_.setTexture(texture);
    sprite_.setPosition(defaultPosition_);
    setFrameRate(AnimationType::Idle, frameRate);
    setFrameRate(AnimationType::Walking, frameRate);
  }

  // enable movement with keys
  void move(sf::Vector2f &velocity, sf::Time frameTime,
            const std::vector<sf::FloatRect> &wallsBounds,
            const sf::RenderWindow &window) {
    // FIX: restore movement function
  }
};

// base class for enemies
class Enemy : public AnimatedObject {
private:
  sf::Vector2f defaultPosition_;
  sf::Vector2f size_;

public:
  // constructor
  Enemy(const sf::Texture &texture, int frameRate)
      : AnimatedObject(), defaultPosition_(50.0f, 300.0f), size_(15.0f, 30.0f) {
    sprite_.setTexture(texture);
    sprite_.setPosition(defaultPosition_);
    setFrameRate(AnimationType::Idle, frameRate);
    setFrameRate(AnimationType::Walking, frameRate);
  }

  // autonomic movement
  void move(sf::Vector2f &velocity, sf::Time frameTime,
            const std::vector<sf::FloatRect> &wallsBounds,
            const sf::RenderWindow &window) {
    // FIX: add auto-movement for enemies
  }
};

// fills the main game vector with all the drawable objects
void fillGameObjects(std::vector<std::unique_ptr<Object>> &gameObjects) {
  sf::Texture idleTexture;
  sf::Texture walkingTexture;
  sf::Texture attackingTexture;
  sf::Texture rollingTexture;

  if (!idleTexture.loadFromFile("textures/"
                                "playerTexture/PlayerAnimationPNG/_Idle.png") ||
      !walkingTexture.loadFromFile("textures/playerTexture/PlayerAnimationPNG/"
                                   "_Run.png") ||
      !attackingTexture.loadFromFile(
          "textures/playerTexture/PlayerAnimationPNG/"
          "_Attack.png") ||
      !rollingTexture.loadFromFile("textures/playerTexture/PlayerAnimationPNG/"
                                   "_Roll.png")) {
    throw std::runtime_error("Failed to load texture file.");
  }

  auto player = std::make_unique<Player>(idleTexture, 10);
  // adjust frame rect
  player->addAnimationFrame(AnimationType::Idle, sf::IntRect(0, 0, 50, 50));
  // add more frames if necessary
  player->addAnimationFrame(AnimationType::Idle, sf::IntRect(50, 0, 50, 50));
  // add frames for other actions
  player->addAnimationFrame(AnimationType::Walking, sf::IntRect(0, 0, 50, 50));
  // Adjust frame rect as needed
  player->addAnimationFrame(AnimationType::Walking, sf::IntRect(50, 0, 50, 50));

  // FIX: add frames for other actions

  // same for enemies
  auto enemy = std::make_unique<Enemy>(idleTexture, 10);
  enemy->addAnimationFrame(AnimationType::Idle, sf::IntRect(0, 0, 50, 50));
  enemy->addAnimationFrame(AnimationType::Idle, sf::IntRect(50, 0, 50, 50));
  enemy->addAnimationFrame(AnimationType::Walking, sf::IntRect(0, 0, 50, 50));
  enemy->addAnimationFrame(AnimationType::Walking, sf::IntRect(50, 0, 50, 50));

  gameObjects.emplace_back(std::move(player));
  gameObjects.emplace_back(std::move(enemy));
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
  window.setFramerateLimit(144);

  std::vector<std::unique_ptr<Object>> gameObjects;
  fillGameObjects(gameObjects);

  std::vector<sf::FloatRect> wallsBounds;
  sf::Vector2f velocity(0.f, 0.f);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Time frameTime = clock.restart();

    // event handling
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { // closing window
        window.close();
      } else if (event.type == sf::Event::KeyPressed) { // input handling
        if (event.key.code == sf::Keyboard::Left) {
          velocity.x = -500.0f;
        } else if (event.key.code == sf::Keyboard::Right) {
          velocity.x = 500.0f;
        } else if (event.key.code == sf::Keyboard::Up) {
          velocity.y = -500.0f;
        } else if (event.key.code == sf::Keyboard::Down) {
          velocity.y = 500.0f;
        }
      } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::Right) {
          velocity.x = 0.0f;
        } else if (event.key.code == sf::Keyboard::Up ||
                   event.key.code == sf::Keyboard::Down) {
          velocity.y = 0.0f;
        }
      }
    }

    // updating states of objects in the game with static cast
    for (auto &obj : gameObjects) {
      obj->update(frameTime);
      Player *player = dynamic_cast<Player *>(obj.get());
      if (player) {
        player->move(velocity, frameTime, wallsBounds, window);
      }
      Enemy *enemy = dynamic_cast<Enemy *>(obj.get());
      if (enemy) {
        enemy->move(velocity, frameTime, wallsBounds, window);
      }
    }

    // draw the objects
    window.clear();
    for (auto &obj : gameObjects) {
      window.draw(*obj);
    }
    window.display();
  }

  return 0;
}
