#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Object : public sf::Drawable {
public:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override = 0;
  virtual ~Object() = default;
};
