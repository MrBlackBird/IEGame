#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window.hpp>
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

  if (!this->ROLLtexture_.loadFromFile("textures/PlayerTexture/_Attack2.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
}

void Player::init_sprite() {
  this->sprite_.setTexture(IDLEtexture_);
  this->currentFrame_ = sf::IntRect(0, 0, 40, 80);
  this->sprite_.setTextureRect(currentFrame_);
  this->sprite_.setScale(3.75f, 3.75f);
}

void Player::init_variables() { this->animationState_ = IDLE; }

void Player::init_animations() { this->animationTimer_.restart(); }

void Player::init_physics() {
  this->maxVelocity_ = 2.f;
  this->minVelocity_ = 1.f;
  this->acceleration_ = 1.5f;
  this->drag_ = 0.93f;
}

void Player::render(sf::RenderTarget &target) { target.draw(this->sprite_); }

// void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//   target.draw(static_cast<const sf::Sprite &>(*this), states);
// }

void Player::move(const float xDir, const float yDir) {
  // acceleration
  this->velocity_.x += xDir * this->acceleration_;
  // NOTE: will be changed for gravity
  // this->velocity_.y += yDir * this->acceleration_;

  // limit velocity
  if (std::abs(this->velocity_.x) > this->maxVelocity_) {
    this->velocity_.x =
        this->maxVelocity_ * ((this->velocity_.x < 0.f) ? -1.f : 1.f);
  }
}

void Player::movement() {
  this->animationState_ = IDLE;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    this->move(-1.f, 0.f);
    this->animationState_ = LEFT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    this->move(1.f, 0.f);
    this->animationState_ = RIGHT;
  }
}

// FIX: fix the animation frame values to reduce blining

void Player::animations() {
  if (this->animationState_ == IDLE) {
    this->sprite_.setTexture(IDLEtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrame_.left += 40.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

  } else if (this->animationState_ == RIGHT) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrame_.left += 40.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

  } else if (this->animationState_ == LEFT) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrame_.left += 40.f;
      if (this->currentFrame_.left >= 1080.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  }
}

void Player::update_physics() {

  // deceleration
  this->velocity_ *= this->drag_;

  // limit deceleration
  if (std::abs(this->velocity_.x) < this->minVelocity_) {
    this->velocity_.x = 0.f;
  }
  if (std::abs(this->velocity_.y) < this->minVelocity_) {
    this->velocity_.y = 0.f;
  }

  this->sprite_.move(this->velocity_);
}

void Player::update() {
  this->movement();
  this->animations();
  this->update_physics();
}

Player::Player() {
  this->init_variables();
  this->init_texture();
  this->init_sprite();
  this->init_animations();
  this->init_physics();
}

Player::~Player() {}
