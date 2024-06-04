#include "gameObject.hpp"
#include <SFML/Graphics.hpp>

class BackGround : public Object {
private:
  sf::Texture NIGHTtexture_;
  sf::Texture CITYtexture_;
  //  sf::Texture GLOWtexture_;
  //  sf::Texture FORESTtexture_;
  sf::Sprite NIGHTsprite_;
  sf::Sprite CITYsprite_;
  //  sf::Sprite GLOWsprite_;
  //  sf::Sprite FORESTsprite_;

  void init_texture();
  void init_sprite();

public:
  BackGround();
  ~BackGround();

  // functions
  void update();
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
