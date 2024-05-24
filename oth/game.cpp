#include "game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>

void Game::init_window() {
  this->window_.create(sf::VideoMode(800, 600), "Dark Souls",
                       sf::Style::Close | sf::Style::Titlebar);
  this->window_.setFramerateLimit(144);
}

const sf::RenderWindow &Game::get_window() const { return this->window_; }

void Game::init_player() { this->player_ = std::make_unique<Player>(); }

void Game::update_player() { this->player_->update(); }

void Game::render_player() { this->player_->render(this->window_); }

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

  // update player in-game
  this->update_player();

  // update collisions
  this->updateCollision();
}

void Game::updateCollision() {
  if (this->player_->get_position().y +
          this->player_->get_global_bounds().height >
      this->window_.getSize().y) {

    this->player_->reset_velocity_y();
    this->player_->set_position(this->player_->get_position().x,
                                this->window_.getSize().y -
                                    this->player_->get_global_bounds().height);
  }
}

void Game::render() {
  this->window_.clear();

  // render stuff
  this->render_player();

  this->window_.display();
}

Game::Game() {
  this->init_window();
  this->init_player();
}

Game::~Game() {}
