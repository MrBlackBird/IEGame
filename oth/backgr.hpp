#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class BackGround {
private:
  sf::Texture texture_;
  sf::Sprite sprite_;

  void init_texture();
  void init_sprite();

public:
  BackGround();
  ~BackGround();

  // functions
  void update();
  void render(sf::RenderTarget &target);
};
