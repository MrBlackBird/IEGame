#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Tile::Tile(sf::Texture &texture, sf::IntRect textureRect, const bool damaging)
    : damaging_(damaging) {
  this->sprite_.setTexture(texture);
  this->sprite_.setTextureRect(textureRect);
}

const sf::FloatRect Tile::get_global_bounds() const {
  return this->sprite_.getGlobalBounds();
}

void Tile::update() {}

void Tile::render(sf::RenderTarget &target) { target.draw(this->sprite_); }
