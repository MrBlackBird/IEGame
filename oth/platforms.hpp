#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <utility>
#include <vector>

class Platform : public Object {
private:
  sf::Texture texture_;
  sf::Sprite sprite_;
  std::vector<sf::Vector2f> positions_;
  std::vector<sf::Shape *> platforms_;
  std::vector<sf::FloatRect> platformsBounds_;

  void init_texture();
  void init_sprite();
  void init_positions();
  void init_platforms();

public:
  Platform();
  ~Platform();

  // functions
  const std::vector<sf::FloatRect> &get_platform_bounds() const {
    return platformsBounds_;
  }
  void update();
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
