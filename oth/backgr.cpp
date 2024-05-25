#include "backgr.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

void BackGround::init_texture() {
  if (!this->texture_.loadFromFile(
          "textures/Enviroment/Medieval_Castle_Asset_Pack/Background/"
          "layer_1.png")) {
    std::cerr << "ERROR: missing background texture" << std::endl;
  }
}

void BackGround::init_sprite() { this->sprite_.setTexture(this->texture_); }

void BackGround::update() {}

void BackGround::render(sf::RenderTarget &target) {
  target.draw(this->sprite_);
}

BackGround::BackGround() {
  this->init_texture();
  this->init_sprite();
}

BackGround::~BackGround() {}
