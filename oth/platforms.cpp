#include "platforms.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

void Platform::init_texture() {}

void Platform::init_sprite() {}

void Platform::init_positions() {
  for (int i = 0; i < 3; i++) {
    sf::Vector2f pos(0.f + (200 * i), 300.f);
    this->positions_.emplace_back(pos);
  }
}

// create a plaftorm for each position pair
//
// FIX: finish making platforms
void Platform::init_platforms() {
  for (auto &position : this->positions_) {
    sf::RectangleShape plfrm(sf::Vector2f(100, 40));
    plfrm.setPosition(position);
  }
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto &platform : this->platforms_) {
    target.draw(platform);
  }
}

void Platform::update() {}

Platform::Platform() {
  this->init_texture();
  this->init_sprite();
  this->init_positions();
}

Platform::~Platform() {}
