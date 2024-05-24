#include "game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <memory>

void Game::init_window() {
  this->window_.create(sf::VideoMode(800, 600), "Dark Souls",
                       sf::Style::Close | sf::Style::Titlebar);
}

const sf::RenderWindow &Game::get_window() const { return this->window_; }

void Game::init_player() { this->player_ = std::make_unique<Player>(); }

void Game::update_player() { this->player_->update(); }

void Game::update() {
  // Polling window events
  while (this->window_.pollEvent(this->event_)) {
    if (this->event_.type == sf::Event::Closed) {
      this->window_.close();
    } else if (this->event_.type == sf::Event::KeyPressed &&
               this->event_.key.code == sf::Keyboard::Escape) {
      this->window_.close();
    }
  }

  // Update player in-game
  this->update_player();
}

void Game::render() {
  this->window_.clear();

  // Render player
  this->window_.draw(*this->player_);

  this->window_.display();
}

Game::Game() {
  this->init_window();
  this->init_player();
}

Game::~Game() {}
