#include "game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>

void Game::init_window() {
  this->window_.create(sf::VideoMode(800, 600), "Dark Souls",
                       sf::Style::Close | sf::Style::Titlebar);
  this->window_.setFramerateLimit(140);
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
  }

  // update player in-game
  this->update_player();
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
