#include "game.hpp"
#include "gameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <memory>

void Game::init_window() {
  this->window_.create(sf::VideoMode(1300, 900), "Dark Souls",
                       sf::Style::Close | sf::Style::Titlebar);
  this->window_.setFramerateLimit(144);
}

const sf::RenderWindow &Game::get_window() const { return this->window_; }

void Game::init_player() {
  this->player_ = std::make_unique<Player>();
  // this->objects_.emplace_back(std::move(player_));
}

// void Game::init_background() {
//   this->backGround_ = std::make_unique<BackGround>();
// }

void Game::update_player(float deltaTime) {
  // for (auto &obj : objects_) {
  //  Player *playerTemp = dynamic_cast<Player *>(obj.get());
  // if (playerTemp) {
  this->player_->update(deltaTime);
  // break;
  //}
  //}
}

void Game::render_objects() {
  //   for (auto &obj : this->objects_) {
  //     obj->draw(this->window_, sf::RenderStates::Default);
  //   }
  this->player_->render(this->window_);
  // this->backGround_->render(this->window_);
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
  // for (auto &obj : objects_) {
  //  Player *playerTemp = dynamic_cast<Player *>(obj.get());
  // if (playerTemp) {
  if (this->player_->get_position().y +
          this->player_->get_global_bounds().height >
      this->window_.getSize().y) {

    this->player_->reset_velocity_y();
    this->player_->set_position(this->player_->get_position().x,
                                this->window_.getSize().y -
                                    this->player_->get_global_bounds().height);
    //   break;
    //}
    //}
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
