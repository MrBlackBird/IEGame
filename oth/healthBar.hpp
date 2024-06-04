#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

class HealthBar : public Object {
private:
  sf::Texture BASEtexture_;
  sf::Texture BORDERtexture_;
  sf::Texture DAMAGEtexture_;
  sf::Sprite BASEsprite_;
  sf::Sprite BORDERsprite_;
  sf::Sprite DAMAGEsprite_;

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
