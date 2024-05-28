#include "game.hpp"
#include "gameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <memory>

void Game::init_window() {
  this->window_.create(sf::VideoMode(1300, 900), "Dark Ages",
                       sf::Style::Close | sf::Style::Titlebar);
  this->window_.setFramerateLimit(240);
}

const sf::RenderWindow &Game::get_window() const { return this->window_; }

void Game::init_player() {
  // create player as unique ptr for polymorphic drawing
  auto player = std::make_unique<Player>();
  // get raw player ptr to avoid issues with class-integrated functions
  this->player_ = player.get();
  // place player into objects vector
  this->objects_.emplace_back(std::move(player));
}

// void Game::init_background() {
//   this->backGround_ = std::make_unique<BackGround>();
// }

void Game::update_player(float deltaTime) {
  if (this->player_) {
    this->player_->update(deltaTime);
  }
}

void Game::render_objects() {
  for (auto &obj : this->objects_) {
    obj->draw(this->window_, sf::RenderStates::Default);
  }
}

void Game::update() {
  // polling window events
  while (this->window_.pollEvent(this->event_)) {

    if (this->event_.type == sf::Event::Closed) {
      this->window_.close();
    } else if (this->event_.type == sf::Event::KeyPressed &&
               this->event_.key.code == sf::Keyboard::Escape) {
      this->window_.close();
    }

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

  // update collisions
  this->updateCollision();
}

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

void Game::render() {
  this->window_.clear();

  // render stuff
  this->render_objects();

  this->window_.display();
}

Game::Game() {
  this->init_window();
  this->init_player();
}

Game::~Game() {}
