#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

void Player::init_texture() {
  // load textures from files
  if (!this->IDLEtexture_.loadFromFile("textures/PlayerTexture/_Idle.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->RUNtexture_.loadFromFile("textures/PlayerTexture/_Run.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->JUMPtexture_.loadFromFile("textures/PlayerTexture/_Jump.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->FALLtexture_.loadFromFile("textures/PlayerTexture/_Fall.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->ROLLtexture_.loadFromFile("textures/PlayerTexture/_Roll.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->ATTACKtexture_.loadFromFile(
          "textures/PlayerTexture/_Attack2.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
}

void Player::init_sprite() {
  // setting core sprite values
  this->sprite_.setTexture(IDLEtexture_);
  this->currentFrame_ = sf::IntRect(0, 0, 120, 80);
  this->sprite_.setTextureRect(currentFrame_);
  this->sprite_.setScale(3.f, 3.f);
  this->sprite_.setPosition(650.f, 900.f);
}

void Player::init_variables() {
  // set core player variables
  this->animationState_ = IDLE;
  this->isGrounded_ = true;
  this->groundLevel_ = 900.f;
  this->isDead_ = false;
}

void Player::init_animations() {
  // initial animation condition
  this->animationTimer_.restart();
  this->animationSwitch_ = true;
}

void Player::init_physics() {
  // set core physics values
  this->maxVelocity_ = 1000.f;
  this->minVelocity_ = 10.f;
  this->acceleration_ = 150.f;
  this->drag_ = 0.6f;
  this->gravity_ = 1000.f;
  this->maxGravitationalVelocity_ = 2000.f;
}

void Player::init_core() {
  this->health_ = 1000;
  this->damage_ = 400;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->sprite_, states);
}

// manages player sprite movement
void Player::move(const float xDir, const float yDir, float deltaTime) {
  this->sprite_.move(xDir * acceleration_ * deltaTime, 0);
}

// manages player animation states and uses move func
void Player::movement(float deltaTime) {
  this->animationState_ = IDLE;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->facingLeft_ = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      this->move(-0.5f, 0.f, deltaTime);
      this->animationState_ = ATTACK;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      this->move(-0.7f, 0.f, deltaTime);
      this->animationState_ = ROLL;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
               this->isGrounded_) {
      this->velocity_.y = -750.f;
      this->isGrounded_ = false;
      this->animationState_ = JUMP;
    } else {
      this->move(-1.f, 0.f, deltaTime);
      this->animationState_ = LEFT;
    }
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    this->facingLeft_ = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      this->move(0.5f, 0.f, deltaTime);
      this->animationState_ = ATTACK;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      this->move(0.7f, 0.f, deltaTime);
      this->animationState_ = ROLL;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
               this->isGrounded_) {
      this->velocity_.y = -750.f;
      this->isGrounded_ = false;
      this->animationState_ = JUMP;
    } else {
      this->move(1.f, 0.f, deltaTime);
      this->animationState_ = RIGHT;
    }

  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
             this->isGrounded_) {
    this->velocity_.y = -750.f;
    this->isGrounded_ = false;
    this->animationState_ = JUMP;

  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    this->animationState_ = ATTACK;

  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    if (facingLeft_) {
      this->move(-1.f, 0.f, deltaTime);
    } else {
      this->move(1.f, 0.f, deltaTime);
    }
    this->animationState_ = ROLL;
  }
}

// manages animations
void Player::animations() {
  if (this->animationState_ == IDLE) {
    this->sprite_.setTexture(IDLEtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.12f ||
        this->get_animation_switch()) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

  } else if (this->animationState_ == RIGHT) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.09f) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

    // set scale for correct sprite orientation | adjust orgin position
    this->sprite_.setScale(3.f, 3.f);
    this->sprite_.setOrigin(0.f, 0.f);

  } else if (this->animationState_ == LEFT) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.09f) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

    this->sprite_.setScale(-3.f, 3.f);
    this->sprite_.setOrigin(this->sprite_.getGlobalBounds().width / 3.f, 0.f);

  } else if (this->animationState_ == JUMP) {
    this->sprite_.setTexture(JUMPtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.3f) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 240.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  } else if (this->animationState_ == ATTACK) {
    this->sprite_.setTexture(ATTACKtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 600.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  } else if (this->animationState_ == ROLL) {
    this->sprite_.setTexture(ROLLtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.07f) {

      this->currentFrame_.left += 120.f;
      if (this->currentFrame_.left >= 1320.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  }
}

void Player::update_physics(float deltaTime) {
  // gravity
  this->velocity_.y += this->gravity_ * deltaTime;

  // limit gravity
  if (std::abs(this->velocity_.y) > this->maxGravitationalVelocity_) {
    this->velocity_.y = this->maxGravitationalVelocity_ *
                        ((this->velocity_.y < 0.f) ? -1.f : 1.f);
  }

  this->sprite_.move(this->velocity_ * deltaTime);

  // check if player is on the ground (for jumping)
  if (this->sprite_.getPosition().y + this->sprite_.getGlobalBounds().height >=
      this->groundLevel_) {
    this->velocity_.y = 0.f;
    this->isGrounded_ = true;
    this->sprite_.setPosition(this->sprite_.getPosition().x,
                              this->groundLevel_ -
                                  this->sprite_.getGlobalBounds().height);
  } else {
    this->isGrounded_ = false;
  }
}

// for smooth animation changing
const bool Player::get_animation_switch() {
  bool tempAnimSwitch = this->animationSwitch_;

  if (this->animationSwitch_) {
    this->animationSwitch_ = false;
  }

  return tempAnimSwitch;
}

// for smooth animation changing
void Player::reset_animation_timer() {
  this->animationTimer_.restart();
  this->animationSwitch_ = true;
}

const sf::Vector2f Player::get_position() const {
  return this->sprite_.getPosition();
}

const sf::FloatRect Player::get_global_bounds() const {
  return this->sprite_.getGlobalBounds();
}

// adjust player bouds for correct collision detection
const sf::FloatRect Player::get_global_bounds_for_platforms() const {
  sf::FloatRect actualGlobalBounds = this->sprite_.getGlobalBounds();
  sf::FloatRect practicalGlobalBounds = actualGlobalBounds;

  practicalGlobalBounds.left += 170.f;
  practicalGlobalBounds.top += 20.f;
  practicalGlobalBounds.width -= 340.f;
  practicalGlobalBounds.height -= 20.f;

  return practicalGlobalBounds;
}

void Player::set_position(const float xCord, const float yCord) {
  this->sprite_.setPosition(xCord, yCord);
}

void Player::reset_velocity_y() { this->velocity_.y = 0.f; }

const sf::Vector2f Player::get_velocity() const { return this->velocity_; }

void Player::set_is_grounded(bool grounded) { this->isGrounded_ = grounded; }

// check for sufficient attacking conditions
bool Player::get_if_attack_state() {
  if (this->animationState_ != ATTACK) {
    return false;
  } else {
    return true;
  }
}

const bool Player::get_is_facing_left() const { return this->facingLeft_; }

void Player::check_death() {
  if (this->health_ <= 0) {
    this->isDead_ = true;
  } else {
    this->isDead_ = false;
  }
}

const bool Player::get_is_dead() const { return this->isDead_; }

void Player::take_damage() { this->health_ -= 1000; }

void Player::update(float deltaTime) {
  this->movement(deltaTime);
  this->animations();
  this->update_physics(deltaTime);
}

Player::Player() {
  this->init_variables();
  this->init_texture();
  this->init_sprite();
  this->init_animations();
  this->init_physics();
  this->init_core();
}

Player::~Player() {}
