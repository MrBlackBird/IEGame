#include "enemy.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
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
  // setting core sprite values
  this->sprite_.setTexture(IDLEtexture_);
  this->currentFrame_ = sf::IntRect(0, 0, 24, 32);
  this->currentFrameWalk_ = sf::IntRect(0, 0, 22, 33);
  this->currentFrameAttack_ = sf::IntRect(0, 0, 43, 37);
  this->sprite_.setTextureRect(currentFrame_);
  this->sprite_.setScale(3.f, 3.f);
}

void Enemy::init_variables() {
  // setting core enemy variables
  this->animationState_ = IDLE_E;
  this->isGrounded_ = true;
  this->groundLevel_ = 900.f;
  this->health_ = 100;
  this->damage_ = 200;
  this->isAlive_ = true;
}

// for smoother animation transitions
void Enemy::init_animations() {
  this->animationTimer_.restart();
  this->animationSwitch_ = true;
}

// set core phisics values
void Enemy::init_physics() {
  this->maxVelocity_ = 1000.f;
  this->minVelocity_ = 10.f;
  this->acceleration_ = 100.f;
  this->drag_ = 0.6f;
  this->gravity_ = 1200.f;
  this->maxGravitationalVelocity_ = 10000.f;
}

void Enemy::init_core() {
  this->health_ = 200.f;
  this->damage_ = 100;
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->sprite_, states);
}

void Enemy::move(const float xDir, const float yDir, float deltaTime) {
  this->sprite_.move(xDir * acceleration_ * deltaTime, 0);
}

// automated enemy movement
void Enemy::chase_player(float playerXenemyDistace, float playerYcord,
                         float deltaTime) {
  if (this->isAlive_) {
    if (playerXenemyDistace + 60.f > 0.f) {
      this->facingLeft_ = false;
      this->animationState_ = RIGHT_E;
      this->sprite_.move(1 * acceleration_ * deltaTime, 0);
    } else if (playerXenemyDistace + 0.f < 0.f) {
      this->facingLeft_ = true;
      this->animationState_ = LEFT_E;
      this->sprite_.move(-1 * acceleration_ * deltaTime, 0);
    } else {
      this->animationState_ = IDLE_E;
    }
    //    if (std::abs(playerXenemyDistace) < 50.f) {
    //      if (playerXenemyDistace < 0.f) {
    //        this->facingLeft_ = true;
    //      }
    //      this->animationState_ = ATTACK_E;
    //      if (facingLeft_ == true) {
    //        this->sprite_.move(-0.5f * acceleration_ * deltaTime, 0);
    //      } else {
    //        this->sprite_.move(0.5f * acceleration_ * deltaTime, 0);
    //      }
    //    }
    if (std::abs(playerXenemyDistace + 60.f) < 30.f) {
      if (playerXenemyDistace + 50.f < 0.f) {
        this->facingLeft_ = false;
      }
      this->animationState_ = ATTACK_E;
      if (facingLeft_ == true) {
        this->sprite_.move(-0.5f * acceleration_ * deltaTime, 0);
        player_hit();
      } else {
        this->sprite_.move(0.5f * acceleration_ * deltaTime, 0);
        player_hit();
      }
    }
  }
}

bool Enemy::player_hit() { return true; }

// manages all enemy animaitons and texture switching
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

      this->currentFrameWalk_.left += 22.f;
      if (this->currentFrameWalk_.left >= 264.f) {
        this->currentFrameWalk_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrameWalk_);
    }

    // set scale for correct sprite orientation & adjust orgin position
    this->sprite_.setScale(3.f, 3.f);
    this->sprite_.setOrigin(0.f, 0.f);

  } else if (this->animationState_ == LEFT_E) {
    this->sprite_.setTexture(RUNtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.09f) {

      this->currentFrameWalk_.left += 22.f;
      if (this->currentFrameWalk_.left >= 264.f) {
        this->currentFrameWalk_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrameWalk_);
    }

    // mirroing sprite when moving left
    this->sprite_.setScale(-3.f, 3.f);
    this->sprite_.setOrigin(this->sprite_.getGlobalBounds().width / 3.f, 0.f);

  } else if (this->animationState_ == ATTACK_E) {
    this->sprite_.setTexture(ATTACKtexture_);

    if (this->animationTimer_.getElapsedTime().asSeconds() >= 0.1f) {

      this->currentFrameAttack_.left += 43.f;
      if (this->currentFrameAttack_.left >= 731.f) {
        this->currentFrameAttack_.left = 0;
      }

      this->animationTimer_.restart();
      this->sprite_.setTextureRect(this->currentFrameAttack_);
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

// adjusted for correct collision detection - changing sprite to visual player
// bounds
const sf::FloatRect Enemy::get_global_bounds_for_platforms() const {
  sf::FloatRect actualGlobalBounds = this->sprite_.getGlobalBounds();
  sf::FloatRect practicalGlobalBounds = actualGlobalBounds;

  practicalGlobalBounds.left += 0.f;
  practicalGlobalBounds.top += 0.f;
  practicalGlobalBounds.width -= 60.f;
  practicalGlobalBounds.height += 0.f;

  return practicalGlobalBounds;
}

const sf::Vector2f Enemy::get_velocity() const { return this->velocity_; }

void Enemy::set_position(const float xCord, const float yCord) {
  this->sprite_.setPosition(xCord, yCord);
}

void Enemy::reset_velocity_y() { this->velocity_.y = 0.f; }

void Enemy::take_damage() {
  if (this->isAlive_) {
    this->health_ -= 100;
  }
}

void Enemy::check_death() {
  if (this->health_ <= 0) {
    this->isAlive_ = false;
    // this->animationState_ = DEATH_E;
    // sf::Texture emptyTexture;
    // this->sprite_.setTexture(emptyTexture);
  } else {
    this->isAlive_ = true;
  }
}

const bool Enemy::get_is_alive() const { return this->isAlive_; }

const float Enemy::get_player_X_enemy_distance() const {
  return this->get_player_X_enemy_distance();
}

void Enemy::set_player_X_enemy_distance(float pXed) {
  this->playerXenemyDistance_ = pXed;
}

void Enemy::update(float playerYcord, float deltaTime) {
  // only updated living enemies
  if (isAlive_) {
    this->animations();
    this->update_physics(deltaTime);
    this->chase_player(this->playerXenemyDistance_, playerYcord, deltaTime);
    this->check_death();
    this->animations();
  } else {
    this->check_death();
  }
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
