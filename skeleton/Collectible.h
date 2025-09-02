#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <SFML/Graphics.hpp>
#include <string>

class Collectible {
public:
    Collectible(float x, float y, float size, const sf::Texture* texture, const sf::IntRect& rect, const std::string& type);

    void draw(sf::RenderTarget& target) const;
    const sf::FloatRect getBounds() const;
    std::string getType() const;

    bool isCollected = false;

private:
    sf::Sprite sprite;
    std::string type;
};

#endif
