#include "platforms.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void Platform::init_texture() {}

void Platform::init_sprite() {}

void Platform::init_positions() {}

// create a plaftorm for each position pair
void Platform::init_platforms() {}

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
