#include "Collectible.h"

Collectible::Collectible(float x, float y, float size, const sf::Texture* texture, const sf::IntRect& rect, const std::string& type)
    : type(type)
{
    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(x, y);
    sprite.setScale(size / rect.width, size / rect.height);
}

void Collectible::draw(sf::RenderTarget& target) const {
    if (!isCollected)
        target.draw(sprite);
}

const sf::FloatRect Collectible::getBounds() const {
    return sprite.getGlobalBounds();
}

std::string Collectible::getType() const {
    return type;
}
