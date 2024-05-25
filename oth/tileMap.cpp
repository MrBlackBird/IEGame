#include "tileMap.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

TileMap::TileMap() {
  this->tileSheet_ = NULL;
  this->tileSize_ = 0;
}

TileMap::TileMap(unsigned width, unsigned height, sf::Texture *tileSheet,
                 unsigned tileSize) {
  this->tileSheet_ = tileSheet;
  this->tileSize_ = tileSize;

  this->tiles_.resize(width);
  for (int i = 0; i < this->tiles_.size(); i++) {
    this->tiles_[i].resize(height, nullptr);
  }
}

TileMap::~TileMap() {
  for (int i = 0; i < this->tiles_.size(); i++) {
    for (int j = 0; j < this->tiles_[i].size(); j++) {
      delete this->tiles_[i][j];
      this->tiles_[i][j] = nullptr;
    }
  }
}

void TileMap::add_tile(unsigned xCord, unsigned yCord) {}

void TileMap::remove_tile(unsigned xCord, unsigned yCord) {}

void TileMap::update() {}

void TileMap::render(sf::RenderTarget &target) {}
