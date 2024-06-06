#include "platforms.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

void Platform::init_texture() {}

void Platform::init_sprite() {}

void Platform::init_positions() {}

// create a plaftorm for each position pair
//
// FIX: testing making platforms
void Platform::init_platforms() {
  sf::RectangleShape *plfrm1 =
      new sf::RectangleShape(sf::Vector2f(100.f, 40.f));
  plfrm1->setPosition(sf::Vector2f(450.f, 700.f));
  plfrm1->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm1->getGlobalBounds());
  this->platforms_.emplace_back(plfrm1);

  sf::RectangleShape *plfrm2 =
      new sf::RectangleShape(sf::Vector2f(100.f, 40.f));
  plfrm2->setPosition(sf::Vector2f(150.f, 700.f));
  plfrm2->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm2->getGlobalBounds());
  this->platforms_.emplace_back(plfrm2);

  sf::RectangleShape *plfrm3 =
      new sf::RectangleShape(sf::Vector2f(100.f, 40.f));
  plfrm3->setPosition(sf::Vector2f(1000.f, 700.f));
  plfrm3->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm3->getGlobalBounds());
  this->platforms_.emplace_back(plfrm3);
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto &platform : this->platforms_) {
    target.draw(*platform);
  }
}

void Platform::update() {}

Platform::Platform() {
  this->init_texture();
  this->init_sprite();
  this->init_platforms();
}

Platform::~Platform() {}
