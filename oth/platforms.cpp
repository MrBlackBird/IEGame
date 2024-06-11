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
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm1->setPosition(sf::Vector2f(0.f, 700.f)); // setting platform position
  plfrm1->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm1->getGlobalBounds());
  this->platforms_.emplace_back(plfrm1);

  sf::RectangleShape *plfrm2 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm2->setPosition(sf::Vector2f(1150.f, 700.f));
  plfrm2->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm2->getGlobalBounds());
  this->platforms_.emplace_back(plfrm2);

  sf::RectangleShape *plfrm3 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm3->setPosition(sf::Vector2f(0.f, 200.f));
  plfrm3->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm3->getGlobalBounds());
  this->platforms_.emplace_back(plfrm3);

  sf::RectangleShape *plfrm4 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm4->setPosition(sf::Vector2f(1150.f, 200.f));
  plfrm4->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm4->getGlobalBounds());
  this->platforms_.emplace_back(plfrm4);

  sf::RectangleShape *plfrm5 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm5->setPosition(sf::Vector2f(500.f, 700.f));
  plfrm5->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm5->getGlobalBounds());
  this->platforms_.emplace_back(plfrm5);

  sf::RectangleShape *plfrm6 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm6->setPosition(sf::Vector2f(650.f, 700.f));
  plfrm6->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm6->getGlobalBounds());
  this->platforms_.emplace_back(plfrm6);

  sf::RectangleShape *plfrm7 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm7->setPosition(sf::Vector2f(500.f, 200.f));
  plfrm7->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm7->getGlobalBounds());
  this->platforms_.emplace_back(plfrm7);

  sf::RectangleShape *plfrm8 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm8->setPosition(sf::Vector2f(650.f, 200.f));
  plfrm8->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm8->getGlobalBounds());
  this->platforms_.emplace_back(plfrm8);

  sf::RectangleShape *plfrm9 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm9->setPosition(sf::Vector2f(250.f, 450.f));
  plfrm9->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm9->getGlobalBounds());
  this->platforms_.emplace_back(plfrm9);

  sf::RectangleShape *plfrm10 =
      new sf::RectangleShape(sf::Vector2f(150.f, 40.f));
  plfrm10->setPosition(sf::Vector2f(975.f, 450.f));
  plfrm10->setFillColor(sf::Color::Black);
  this->platformsBounds_.emplace_back(plfrm10->getGlobalBounds());
  this->platforms_.emplace_back(plfrm10);
}

// overloading drawing
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
