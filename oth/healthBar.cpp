#include "healthBar.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

void HealthBar::init_texture() {
  // creat multi-layer textures
  if (!this->BASEtexture_.loadFromFile(
          "textures/Enviroment/Medieval_Castle_Asset_Pack/HUD/"
          "health_bar.png")) {
    std::cerr << "Error: missing health bar texture" << std::endl;
  }
  if (!this->BORDERtexture_.loadFromFile(
          "textures/Enviroment/Medieval_Castle_Asset_Pack/HUD/bar.png")) {
    std::cerr << "Error: missing health bar texture" << std::endl;
  }
  if (!this->DAMAGEtexture_.loadFromFile(
          "textures/Enviroment/ "
          "Medieval_Castle_Asset_Pack/HUD/bar_background.png")) {
    std::cerr << "Error: missing health bar texture" << std::endl;
  }
}

void HealthBar::init_sprite() {
  // set core sprite values
  this->BASEsprite_.setTexture(this->BASEtexture_);
  this->BASEsprite_.setPosition(0.f, 0.f);
  this->BASEsprite_.setScale(1.f, 1.f);

  this->BORDERsprite_.setTexture(this->BORDERtexture_);
  this->BORDERsprite_.setPosition(0.f, 0.f);
  this->BORDERsprite_.setScale(1.f, 1.f);

  this->DAMAGEsprite_.setTexture(this->DAMAGEtexture_);
  this->DAMAGEsprite_.setPosition(0.f, 0.f);
  this->DAMAGEsprite_.setScale(1.f, 1.f);
}

void HealthBar::update() {}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->BASEsprite_, states);
  target.draw(this->BORDERsprite_, states);
  target.draw(this->DAMAGEsprite_, states);
}

HealthBar::HealthBar() {
  this->init_texture();
  this->init_sprite();
}

HealthBar::~HealthBar() {}
