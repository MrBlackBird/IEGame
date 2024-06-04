#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

class Platform : public Object {
private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::vector<sf::Vector2f> positions_;
  std::vector<sf::Drawable> platforms_;

  void init_texture();
  void init_sprite();
  void init_positions();
  void init_platforms();

public:
  Platform();
  ~Platform();

  // functions
  void update();
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
