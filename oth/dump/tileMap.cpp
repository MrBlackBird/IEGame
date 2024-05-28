#include "tileMap.hpp"
#include <SFML/Graphics/Rect.hpp>
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

void TileMap::add_tile(unsigned xCord, unsigned yCord) {
  if (xCord < this->tiles_.size()) {
    if (yCord < this->tiles_[xCord].size()) {
      if (this->tiles_[xCord][yCord] != nullptr) {
        this->tiles_[xCord][yCord] =
            new Tile(this->tileSheet_,
                     sf::IntRect(0, 0, this->tileSize_, this->tileSize_));
      }
    }
  }
}

void TileMap::remove_tile(unsigned xCord, unsigned yCord) {
  if (xCord < this->tiles_.size()) {
    if (yCord < this->tiles_[xCord].size()) {
      if (this->tiles_[xCord][yCord] != nullptr) {
        delete this->tiles_[xCord][yCord];
        this->tiles_[xCord][yCord] = nullptr;
      }
    }
  }
}

void TileMap::update() {
  for (int i = 0; i < this->tiles_.size(); i++) {
    for (int j = 0; j < this->tiles_[i].size(); j++) {
      if (this->tiles_[i][j] != nullptr) {
        this->tiles_[i][j]->update();
      }
    }
  }
}

void TileMap::render(sf::RenderTarget &target) {
  for (int i = 0; i < this->tiles_.size(); i++) {
    for (int j = 0; j < this->tiles_[i].size(); j++) {
      if (this->tiles_[i][j] != nullptr) {
        this->tiles_[i][j]->render(target);
      }
    }
  }
}
