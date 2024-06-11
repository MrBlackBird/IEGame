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
  // set initial position
  this->player_->set_position(500.f, 900.f);
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
  auto enemy1 = std::make_unique<Enemy>();
  this->enemy1_ = enemy1.get();
  // set initial enemy position
  this->enemy1_->set_position(0.f, 0.f);
  this->enemies_.emplace_back(enemy1_);
  this->objects_.emplace_back(std::move(enemy1));
}

void Game::init_enemy_two() {
  auto enemy2 = std::make_unique<Enemy>();
  this->enemy2_ = enemy2.get();
  this->enemy2_->set_position(1200.f, 200.f);
  this->enemies_.emplace_back(enemy2_);
  this->objects_.emplace_back(std::move(enemy2));
}

void Game::init_enemy_three() {
  auto enemy3 = std::make_unique<Enemy>();
  this->enemy3_ = enemy3.get();
  this->enemy3_->set_position(300.f, 900.f);
  this->enemies_.emplace_back(enemy3_);
  this->objects_.emplace_back(std::move(enemy3));
}

void Game::init_platforms() {
  auto platforms = std::make_unique<Platform>();
  this->platforms_ = platforms.get();
  this->objects_.emplace_back(std::move(platforms));
}

//  update player parameteres
void Game::update_player(float deltaTime) {
  // added 'if' for checking for nullptr
  for (auto &enemy : enemies_) {
    if (this->player_) {
      this->player_->update(deltaTime);

      // update global player position
      this->playerXPosition_ = this->player_->get_position().x;
      this->playerXenemyDistance_ =
          this->player_->get_position().x - enemy->get_position().x;

      enemy->set_player_X_enemy_distance(this->player_->get_position().x -
                                         enemy->get_position().x);

      // attacking
      if (this->player_->get_if_attack_state() == true) {
        // check for enemy in range
        if (this->playerXenemyDistance_ < 0 &&
            this->player_->get_is_facing_left() == false) {
          if (playerXenemyDistance_ > -100.f) {
            // count attack
            enemy->take_damage();
          }
        } else if (this->playerXenemyDistance_ > 0 &&
                   this->player_->get_is_facing_left() == true) {
          if (playerXenemyDistance_ < 100.f) {
            enemy->take_damage();
          }
        }
      }
    }
  }
}

//  update enemy parameteres
void Game::update_enemy(float deltaTime) {
  // added 'if' for checking for nullptr
  for (auto &enemy : this->enemies_) {
    if (enemy) {
      enemy->update(this->player_->get_position().y, deltaTime);
    }
    bool kill = enemy->player_hit();
    if (kill) {
      this->player_killed(true);
    }
  }

  // FIX: intended to delete the killed enemy but run into issues

  //  for (auto &obj : this->objects_) {
  //    auto enemyTemp = dynamic_cast<Enemy *>(obj.get());
  //    if (enemyTemp->get_is_alive() == false) {
  //      auto it =
  //          std::find(this->objects_.begin(), this->objects_.end(),
  //          enemyTemp);
  //      this->objects_.erase(it); // remove the element from its current
  //      position
  //    }
  //  }
}

void Game::update_score() {
  this->score_ = 0;
  for (auto &enemy : this->enemies_) {
    if (enemy->get_is_alive() == false) {
      this->score_ += 200;
    }
  }
}

// for adding levels
void Game::update_platforms() {}

// draws all game objects from the objects_ vector of unique_ptr's
void Game::render_objects() {
  for (auto &obj : this->objects_) {
    if (obj) {
      obj->draw(this->window_, sf::RenderStates::Default);
    }
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

    // FIX: left and right window bounds not working properly

    //    if (this->player_->get_position().x +
    //            this->player_->get_global_bounds().width >=
    //        this->window_.getSize().x) {
    //
    //      this->player_->set_position(
    //          this->window_.getSize().x -
    //              this->player_->get_global_bounds_for_platforms().left +
    //              this->player_->get_global_bounds().width,
    //          this->player_->get_position().y);
    //    }

    // for platforms
    for (auto &plfrBounds : this->platforms_->get_platform_bounds()) {
      if (this->player_->get_global_bounds_for_platforms().intersects(
              plfrBounds)) {
        // check if the player is falling down onto the platform
        if (this->player_->get_velocity().y > 0.f) { // Falling down
          // place the player on top of the platform
          this->player_->set_position(
              this->player_->get_position().x,
              plfrBounds.top - this->player_->get_global_bounds().height);
          this->player_->reset_velocity_y();
          this->player_->set_is_grounded(true);
        }
        // check if the player is moving up into the platform
        else if (this->player_->get_velocity().y < 0.f) { // Moving up
          // place the player below the platform
          this->player_->set_position(this->player_->get_position().x,
                                      plfrBounds.top + plfrBounds.height);
          this->player_->reset_velocity_y();
        }
      }
    }
  }

  // for enemie
  for (auto &enemy : this->enemies_) {
    if (enemy && enemy->get_is_alive() == true) {
      if (enemy->get_position().y + enemy->get_global_bounds().height >
          this->window_.getSize().y) {

        enemy->reset_velocity_y();
        enemy->set_position(enemy->get_position().x,
                            this->window_.getSize().y -
                                enemy->get_global_bounds().height);
      }
    }
    // for platforms
    for (auto &plfrBounds : this->platforms_->get_platform_bounds()) {
      if (enemy->get_global_bounds_for_platforms().intersects(plfrBounds)) {
        // Check if the player is falling down onto the platform
        if (enemy->get_velocity().y > 0.f) { // Falling down
          // Place the player on top of the platform
          enemy->set_position(enemy->get_position().x,
                              plfrBounds.top -
                                  enemy->get_global_bounds().height);
          enemy->reset_velocity_y();
        }
        // Check if the player is moving up into the platform
        else if (enemy->get_velocity().y < 0.f) { // Moving up
          // Place the player below the platform
          enemy->set_position(this->player_->get_position().x,
                              plfrBounds.top + plfrBounds.height);
          enemy->reset_velocity_y();
        }
      }
    }
  }
}

// redner objects on the screen
void Game::render() {
  this->window_.clear();

  // render objects
  this->render_objects();

  this->window_.display();
}

// check if player is dead
void Game::player_killed(bool killed) { this->player_->isDead_ = killed; }

bool Game::get_if_player_dead() { return this->player_->get_is_dead(); }

int Game::get_score() { return this->score_; }

// game over message
void Game::game_over() {
  // clear screen
  this->window_.clear();

  // set game over message and its font

  sf::Font font;
  font.loadFromFile("/textures/0xProtoNerdFont-Regular.ttf");
  sf::Text text;
  sf::Text score;
  text.setFont(font);
  text.setString("GAME OVER");
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(100, 100);

  // show game over screen
  this->window_.draw(text);
  this->window_.draw(score);
}

Game::Game() {
  this->init_window();
  this->init_background();
  this->init_enemy();
  this->init_enemy_two();
  this->init_enemy_three();
  this->init_player();
  this->init_platforms();
}

Game::~Game() {}
