#include "player.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

void Player::init_texture() {
  // Load a texture from file
  if (!this->texture_.loadFromFile("path_to_texture.png")) {
    std::cerr << "Error loading player texture" << std::endl;
  }
}

void Player::init_sprite() {
  // Set the texture to the sprite
  this->setTexture(this->texture_);
}

void Player::update() {
  // Implement player update logic here
}

void Player::render(sf::RenderTarget &target) {}

// void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//   target.draw(static_cast<const sf::Sprite &>(*this), states);
// }

Player::Player() {
  this->init_texture();
  this->init_sprite();
}

Player::~Player() {}
