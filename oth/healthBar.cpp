#include "healthBar.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

void HealthBar::init_texture() {
  if (!this->texture_.loadFromFile("PATH TO TEXTURE")) {
    std::cerr << "Error: missing player texture" << std::endl;
  }
}

void HealthBar::init_sprite() {
  this->sprite_.setTexture(this->texture_);
  this->sprite_.setPosition(0.f, 0.f);
  this->sprite_.setScale(1.f, 1.f);
}

void HealthBar::update() {}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->sprite_, states);
}

HealthBar::HealthBar() {
  this->init_texture();
  this->init_sprite();
}

HealthBar::~HealthBar() {}
