#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

// for polymorphism
class Object : public sf::Drawable {
public:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override = 0;
  virtual ~Object() = default;
};

#endif // GAME_OBJECT_HPP
