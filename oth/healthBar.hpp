#include "gameObject.hpp"
#include <SFML/Graphics.hpp>

class HealthBar : public Object {
private:
  sf::Texture texture_;
  sf::Sprite sprite_;

  void init_texture();
  void init_sprite();

public:
  // functions
  void update();
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // constructor & destructor
  HealthBar();
  ~HealthBar();
};
