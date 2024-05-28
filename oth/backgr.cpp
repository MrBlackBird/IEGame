#include "backgr.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

void BackGround::init_texture() {
  if (!this->NIGHTtexture_.loadFromFile(
          "textures/Enviroment/Medieval_Castle_Asset_Pack/Background/"
          "layer_1.png")) {
    std::cerr << "ERROR: missing background texture" << std::endl;
  }
  //  if (!this->CITYtexture_.loadFromFile(
  //          "textures/Enviroment/Medieval_Castle_Asset_Pack/Background/"
  //          "layer_2.png")) {
  //    std::cerr << "ERROR: missing background texture" << std::endl;
  //  }
  //  if (!this->GLOWtexture_.loadFromFile(
  //          "textures/Enviroment/Medieval_Castle_Asset_Pack/Background/"
  //          "layer_3.png")) {
  //    std::cerr << "ERROR: missing background texture" << std::endl;
  //  }
}

void BackGround::init_sprite() {
  this->NIGHTsprite_.setTexture(this->NIGHTtexture_);
  this->NIGHTsprite_.setScale(sf::Vector2f(4.5f, 5.f));
  //  this->CITYsprite_.setTexture(this->NIGHTtexture_);
  //  this->CITYsprite_.setScale(sf::Vector2f(4.1f, 4.5f));
  //  this->GLOWsprite_.setTexture(this->NIGHTtexture_);
  //  this->GLOWsprite_.setScale(sf::Vector2f(4.1f, 4.5f));
}

void BackGround::update() {}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->NIGHTsprite_, states);
  //  target.draw(this->CITYsprite_, states);
  //  target.draw(this->GLOWsprite_, states);
}

BackGround::BackGround() {
  this->init_texture();
  this->init_sprite();
}

BackGround::~BackGround() {}
