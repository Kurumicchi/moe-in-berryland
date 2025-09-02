#include "Platform.h"

Platform::Platform(float x, float y, float width, float height, const sf::Texture* texture, const sf::IntRect& textureRect) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (texture) {
        shape.setTexture(texture);
        shape.setTextureRect(textureRect); // Only show a small part of the big image
    } else {
        shape.setFillColor(sf::Color(150, 75, 0));
    }
}

void Platform::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

const sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}