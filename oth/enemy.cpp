#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

void Enemy::init_texture() {
  // load textures from files
  if (!this->IDLEtexture_.loadFromFile(
          "textures/EnemieTexture/Skeleton/Sprite Sheets/Skeleton Idle.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }

  if (!this->RUNtexture_.loadFromFile(
          "textures/EnemieTexture/Skeleton/Sprite Sheets/Skeleton Walk.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
  if (!this->ATTACKtexture_.loadFromFile("textures/EnemieTexture/Skeleton/"
                                         "Sprite Sheets/Skeleton Attack.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
  if (!this->DEATHtexture_.loadFromFile(
          "textures/EnemieTexture/Skeleton/Sprite Sheets/Skeleton Dead.png")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
}

void Enemy::init_sprite() {
  this->sprite_.setTexture(IDLEtexture_);
  this->currentFrame_ = sf::IntRect(0, 0, 24, 32);
  this->sprite_.setTextureRect(currentFrame_);
  this->sprite_.setScale(3.f, 3.f);
}

void Enemy::init_variables() {
  this->animationState_ = IDLE_E;
  this->isGrounded_ = true;
  this->groundLevel_ = 900.f;
  this->distanceToPlayer_ = 0;
}

void Enemy::init_animations() {
  this->animationTimer_.restart();
  this->animationSwitch_ = true;
}

void Enemy::init_physics() {
  this->maxVelocity_ = 1000.f;
  this->minVelocity_ = 10.f;
  this->acceleration_ = 200.f;
  this->drag_ = 0.6f;
  this->gravity_ = 1200.f;
  this->maxGravitationalVelocity_ = 10000.f;
}

void Enemy::init_core() {
  this->health_ = 200;
  this->damage_ = 100;
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->sprite_, states);
}

void Enemy::move(const float xDir, const float yDir, float deltaTime) {
  this->sprite_.move(xDir * acceleration_ * deltaTime, 0);
}

void Enemy::chase_player(Player &player, float deltaTime) {
  if (this->distanceToPlayer_ > 0 && this->distanceToPlayer_ < 200.f) {
    this->facingLeft_ = true;
    this->animationState_ = LEFT_E;
    this->sprite_.move(-1 * acceleration_ * deltaTime, 0);
  } else if (distanceToPlayer_ < 0 && this->distanceToPlayer_ < -200.f) {
    this->facingLeft_ = true;
    this->animationState_ = RIGHT_E;
    this->sprite_.move(1 * acceleration_ * deltaTime, 0);
  } else {
    this->animationState_ = IDLE_E;
  }
  if (this->distanceToPlayer_ < 100.f || this->distanceToPlayer_ > -100.f) {
    this->animationState_ = ATTACK_E;
    this->sprite_.move(0.7f * acceleration_ * deltaTime, 0);
  }
}

// FIX: use bool facingLeft to manage '-' in move functions

void Enemy::animations() {
  if (this->animationState_ == IDLE_E) {
    this->sprite_.setTexture(IDLEtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.12f) {

      this->currentFrame_.left += 24.f;
      if (this->currentFrame_.left >= 240.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

  } else if (this->animationState_ == RIGHT_E) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.09f) {

      this->currentFrame_.left += 22.f;
      if (this->currentFrame_.left >= 264.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

    // set scale for correct sprite orientation & adjust orgin position
    this->sprite_.setScale(3.f, 3.f);
    this->sprite_.setOrigin(0.f, 0.f);

  } else if (this->animationState_ == LEFT_E) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.09f) {

      this->currentFrame_.left += 22.f;
      if (this->currentFrame_.left >= 264.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }

    this->sprite_.setScale(-3.f, 3.f);
    this->sprite_.setOrigin(this->sprite_.getGlobalBounds().width / 3.f, 0.f);

  } else if (this->animationState_ == ATTACK_E) {
    this->sprite_.setTexture(ATTACKtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrame_.left += 43.f;
      if (this->currentFrame_.left >= 731.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  } else if (this->animationState_ == DEATH_E) {

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.07f) {

      this->currentFrame_.left += 33.f;
      if (this->currentFrame_.left >= 462.f) {
        this->currentFrame_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrame_);
    }
  }
}

void Enemy::update_physics(float deltaTime) {
  // gravity
  this->velocity_.y += this->gravity_ * deltaTime;

  //  limit gravity
  if (std::abs(this->velocity_.y) > this->maxGravitationalVelocity_) {
    this->velocity_.y = this->maxGravitationalVelocity_ *
                        ((this->velocity_.y < 0.f) ? -1.f : 1.f);
  }

  this->sprite_.move(this->velocity_ * deltaTime);
}

const sf::Vector2f Enemy::get_position() const {
  return this->sprite_.getPosition();
}

const sf::FloatRect Enemy::get_global_bounds() const {
  return this->sprite_.getGlobalBounds();
}

void Enemy::set_position(const float xCord, const float yCord) {
  this->sprite_.setPosition(xCord, yCord);
}

void Enemy::reset_velocity_y() { this->velocity_.y = 0.f; }

void Enemy::update_distance_to_player(float playerXPosition) {
  this->distanceToPlayer_ = this->get_position().x - playerXPosition;
}

void Enemy::update(float playerXPosition, float deltaTime) {
  this->animations();
  this->update_physics(deltaTime);
  this->update_distance_to_player(playerXPosition);
}

Enemy::Enemy() {
  this->init_variables();
  this->init_texture();
  this->init_sprite();
  this->init_animations();
  this->init_physics();
  this->init_core();
}

Enemy::~Enemy() {}