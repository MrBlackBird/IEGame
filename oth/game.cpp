#include "game.hpp"
#include "gameObject.hpp"
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

//  update player parameteres
void Game::update_player(float deltaTime) {
  // added 'if' for checking for nullptr
  if (this->player_) {
    this->player_->update(deltaTime);
  }
}

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

  // update collisions in-game
  this->updateCollision();
}

// checking player for collsions
void Game::updateCollision() {
  if (this->player_) {
    if (this->player_->get_position().y +
            this->player_->get_global_bounds().height >
        this->window_.getSize().y) {

      this->player_->reset_velocity_y();
      this->player_->set_position(
          this->player_->get_position().x,
          this->window_.getSize().y -
              this->player_->get_global_bounds().height);
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
}

Game::~Game() {}
