#include "game.hpp"
#include "gameObject.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <memory>

void Game::init_window() {
  // create window
  this->window_.create(sf::VideoMode(1300, 900), "Dark Ages",
                       sf::Style::Close | sf::Style::Titlebar);
  // set frame rate limit
  this->window_.setFramerateLimit(240);
}

// getter for the window
const sf::RenderWindow &Game::get_window() const { return this->window_; }

// create player object and pointers
void Game::init_player() {
  // create player as unique ptr for polymorphic drawing
  auto player = std::make_unique<Player>();
  // get raw player ptr to avoid issues with class-integrated functions
  this->player_ = player.get();
  // place player into objects vector
  this->objects_.emplace_back(std::move(player));
}

// create background object and pointers
void Game::init_background() {
  // same principal as in init_player()
  auto backGround1 = std::make_unique<BackGround>();
  this->backGround_ = backGround1.get();
  this->objects_.emplace_back(std::move(backGround1));
}

void Game::init_health_bar() {
  auto healthBar = std::make_unique<HealthBar>();
  this->healthBar_ = healthBar.get();
  this->objects_.emplace_back(std::move(healthBar));
}

void Game::init_enemy() {
  auto enemy = std::make_unique<Enemy>();
  this->enemy_ = enemy.get();
  this->objects_.emplace_back(std::move(enemy));
}

void Game::init_platforms() {
  auto platforms = std::make_unique<Platform>();
  this->platforms_ = platforms.get();
  this->objects_.emplace_back(std::move(platforms));
}

//  update player parameteres
void Game::update_player(float deltaTime) {
  // added 'if' for checking for nullptr
  if (this->player_) {
    this->player_->update(deltaTime);

    // update global player position
    this->playerXPosition_ = this->player_->get_position().x;
    this->playerXenemyDistance_ =
        this->player_->get_position().x - this->enemy_->get_position().x;

    // attacking
    if (this->player_->get_if_attack_state() == true) {
      // check for enemy in range
      if (this->playerXenemyDistance_ < 0 &&
          this->player_->get_is_facing_left() == false) {
        if (playerXenemyDistance_ > -100.f) {
          // count attack
          this->enemy_->take_damage();
        }
      } else if (this->playerXenemyDistance_ > 0 &&
                 this->player_->get_is_facing_left() == true) {
        if (playerXenemyDistance_ < 100.f) {
          this->enemy_->take_damage();
        }
      }
    }
  }
}

//  update enemy parameteres
void Game::update_enemy(float deltaTime) {
  // added 'if' for checking for nullptr
  if (this->enemy_) {
    this->enemy_->update(this->playerXPosition_, deltaTime);
  }
}

void Game::update_platforms() {}

// draws all game objects from the objects_ vector of unique_ptr's
void Game::render_objects() {
  for (auto &obj : this->objects_) {
    obj->draw(this->window_, sf::RenderStates::Default);
  }
}

// update the state of the game while running
void Game::update() {
  // polling window events
  while (this->window_.pollEvent(this->event_)) {

    // closing
    if (this->event_.type == sf::Event::Closed) {
      this->window_.close();
    } else if (this->event_.type == sf::Event::KeyPressed &&
               this->event_.key.code == sf::Keyboard::Escape) {
      this->window_.close();
    }

    // inputs for animation delay cancelling
    if (this->event_.type == sf::Event::KeyReleased &&
        (this->event_.key.code == sf::Keyboard::A ||
         this->event_.key.code == sf::Keyboard::W ||
         this->event_.key.code == sf::Keyboard::A ||
         this->event_.key.code == sf::Keyboard::S ||
         this->event_.key.code == sf::Keyboard::D)) {
      this->player_->reset_animation_timer();
    }
  }

  // calculate delta time
  this->deltaTime_ = this->clock_.restart().asSeconds();

  // update player in-game
  this->update_player(deltaTime_);

  // update enemy in-game
  this->update_enemy(deltaTime_);

  // update platforms
  this->update_platforms();

  // update collisions in-game
  this->updateCollision();
}

// checking player for collsions
void Game::updateCollision() {
  // for player
  if (this->player_) {
    // for window bounds
    if (this->player_->get_position().y +
            this->player_->get_global_bounds().height >
        this->window_.getSize().y) {

      this->player_->reset_velocity_y();
      this->player_->set_position(
          this->player_->get_position().x,
          this->window_.getSize().y -
              this->player_->get_global_bounds().height);
    }

    // for platforms
    for (auto &plfrBounds : this->platforms_->get_platform_bounds()) {
      if (this->player_->get_global_bounds_for_platforms().intersects(
              plfrBounds)) {
        // Check if the player is falling down onto the platform
        if (this->player_->get_velocity().y > 0.f) { // Falling down
          // Place the player on top of the platform
          this->player_->set_position(
              this->player_->get_position().x,
              plfrBounds.top - this->player_->get_global_bounds().height);
          this->player_->reset_velocity_y();
          this->player_->set_is_grounded(true);
        }
        // Check if the player is moving up into the platform
        else if (this->player_->get_velocity().y < 0.f) { // Moving up
          // Place the player below the platform
          this->player_->set_position(this->player_->get_position().x,
                                      plfrBounds.top + plfrBounds.height);
          this->player_->reset_velocity_y();
        }
      }
    }
  }

  // for enemie
  if (this->enemy_) {
    if (this->enemy_->get_position().y +
            this->enemy_->get_global_bounds().height >
        this->window_.getSize().y) {

      this->enemy_->reset_velocity_y();
      this->enemy_->set_position(this->enemy_->get_position().x,
                                 this->window_.getSize().y -
                                     this->enemy_->get_global_bounds().height);
    }
  }
  // for platforms
  for (auto &plfrBounds : this->platforms_->get_platform_bounds()) {
    if (this->enemy_->get_global_bounds_for_platforms().intersects(
            plfrBounds)) {
      // Check if the player is falling down onto the platform
      if (this->enemy_->get_velocity().y > 0.f) { // Falling down
        // Place the player on top of the platform
        this->enemy_->set_position(
            this->enemy_->get_position().x,
            plfrBounds.top - this->enemy_->get_global_bounds().height);
        this->enemy_->reset_velocity_y();
      }
      // Check if the player is moving up into the platform
      else if (this->enemy_->get_velocity().y < 0.f) { // Moving up
        // Place the player below the platform
        this->enemy_->set_position(this->player_->get_position().x,
                                   plfrBounds.top + plfrBounds.height);
        this->enemy_->reset_velocity_y();
      }
    }
  }
}

// redner objects on the screen
void Game::render() {
  this->window_.clear();

  // render stuff
  this->render_objects();

  this->window_.display();
}

Game::Game() {
  this->init_window();
  this->init_background();
  this->init_enemy();
  this->init_player();
  this->init_platforms();
}

Game::~Game() {}
