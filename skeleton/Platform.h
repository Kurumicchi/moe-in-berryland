#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(float x, float y, float width, float height, const sf::Texture* texture, const sf::IntRect& textureRect);

    void draw(sf::RenderTarget& target) const;
    const sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
};

#endif