#include "Player.h"
#include "constants.h"
#include "Platform.h"
#include <iostream>
#include <memory>

Player::Player() {
    // Idle anim
    for (int i = 1; i <= 16; ++i) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/Cute Girl/Idle (" + std::to_string(i) + ").png")) {
            std::cout << "Failed to load Idle (" << i << ").png" << std::endl;
        }
        idleFrames.push_back(texture);
    }

    // Walk anim
    for (int i = 1; i <= 20; ++i) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/Cute Girl/Walk (" + std::to_string(i) + ").png")) {
            std::cout << "Failed to load Walk (" << i << ").png" << std::endl;
        }
        walkFrames.push_back(texture);
    }

    // Jump anim
    for (int i = 1; i <= 30; ++i) {
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/Cute Girl/Jump (" + std::to_string(i) + ").png")) {
            std::cout << "Failed to load Jump (" << i << ").png" << std::endl;
        }
        jumpFrames.push_back(texture);
    }

    sprite.setTexture(*idleFrames[0]);

    sprite.setPosition(100.f, 100.f);
    sprite.setScale(0.3f, 0.3f);
    speed = 3.0f;
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, 0.f);
    direction = 1;


    // Frame
    currentFrame = 0;
    sprite.setTexture(*idleFrames[currentFrame]);
    frameTimer = 0.0f;
    frameDelay = 0.3f; // seconds between frames

    // Player gravity & Ground detection
    velocity = {0.f, 0.f};
    isOnGround = false;

    // Player animation state
    currentAnim = AnimationState::Idle;
}

// Handle Moe's input
void Player::handleInput() {
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = speed;
        direction = 1;
        currentAnim = AnimationState::Walk;
        isMoving = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -speed;
        direction = -1;
        currentAnim = AnimationState::Walk;
        isMoving = true;
    } else {
        velocity.x = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isOnGround) {
        velocity.y = -12.0f;
        isOnGround = false;
        currentAnim = AnimationState::Jump;
    }
}

// Update Moe's position and apply gravity
void Player::applyPhysics() {
    if (!isOnGround)
        velocity.y += 0.5f;

    if (velocity.y > 5.f)
        velocity.y = 5.f;
}

// Moe moves based on velocity and checks for collisions with platforms
void Player::move(const std::vector<Platform>& platforms) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();

    // Horizontal move
    sprite.move(velocity.x, 0.f);
    sf::FloatRect newBoundsX = getCollisionBounds();

    for (const Platform& plat : platforms) {
        sf::FloatRect platBounds = plat.getBounds();

        bool verticalOverlap =
            sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > platBounds.top + 5.f &&
            sprite.getGlobalBounds().top < platBounds.top + platBounds.height - 5.f;

        if (newBoundsX.intersects(platBounds) && verticalOverlap) {
            sprite.move(-velocity.x, 0.f); // Undo horizontal move
            velocity.x = 0.f;
            break;
        }
    }

    // Vertical move
    sprite.move(0.f, velocity.y);
    sf::FloatRect newBoundsY = sprite.getGlobalBounds();

    for (const Platform& plat : platforms) {
        sf::FloatRect platBounds = plat.getBounds();

        // Moe is jumping and hits the underside of a platform
        if (velocity.y < 0.f && newBoundsY.intersects(platBounds)) {
            float headX = newBoundsY.left + newBoundsY.width / 2.f;
            float headY = newBoundsY.top;

            bool isUnderPlatform =
            headX >= platBounds.left &&
            headX <= platBounds.left + platBounds.width &&
            headY <= platBounds.top + platBounds.height &&
            headY >= platBounds.top;

            if (isUnderPlatform) {
                float platformBottom = platBounds.top + platBounds.height;
                sprite.setPosition(sprite.getPosition().x, platformBottom);
                velocity.y = 0.f;
                break;
            }
        }

    }

    // Feet check — is Moe still standing?
    bool stillStanding = false;
    sf::FloatRect feet = getFeetHitbox();
    float feetX = feet.left + feet.width / 2.f;
    float playerBottom = feet.top + feet.height;

    for (const Platform& plat : platforms) {
        sf::FloatRect platBounds = plat.getBounds();

        bool feetAbovePlatform =
            feetX >= platBounds.left &&
            feetX <= platBounds.left + platBounds.width &&
            std::abs(playerBottom - platBounds.top) <= 5.0f;

        if (feetAbovePlatform) {
            stillStanding = true;
            break;
        }
    }

    if (!stillStanding) {
        setOnGround(false); // Moe walked off a ledge or just jumped
    }
}

// Moe Animation
void Player::updateAnimation() {
    // Update animation based on current state
    if (!isOnGround) {
        currentAnim = AnimationState::Jump;
    }
    else if (velocity.x != 0) {
        currentAnim = AnimationState::Walk;
    }
    else {
        currentAnim = AnimationState::Idle;
    }

    // Update frame timer
    frameTimer += frameDelay;

    if (frameTimer >= frameDelay) {
        frameTimer = 0.0f;
        currentFrame++;

        switch (currentAnim) {
            case AnimationState::Idle:
                if (currentFrame >= idleFrames.size()) currentFrame = 0;
                sprite.setTexture(*idleFrames[currentFrame]);
                break;

            case AnimationState::Walk:
                if (currentFrame >= walkFrames.size()) currentFrame = 0;
                sprite.setTexture(*walkFrames[currentFrame]);
                break;

            case AnimationState::Jump:
                if (currentFrame >= jumpFrames.size()) currentFrame = 0;
                sprite.setTexture(*jumpFrames[currentFrame]);
                break;
        }
    }

    // Flip Moe based on direction
    sprite.setScale(direction * 0.3f, 0.3f);
}


// Draw Moe
void Player::draw(sf::RenderTarget& target) {
    if (!sprite.getTexture()) {
        std::cout << "ERROR: Moe's sprite texture is null!\n";
        return;
    }
    target.draw(sprite);
}


sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}


// Moe Hitbox
sf::FloatRect Player::getFeetHitbox() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float feetWidth = bounds.width * 0.3f;  // narrow feet hitbox
    float feetX = bounds.left + (bounds.width - feetWidth) / 2.f;
    float feetY = bounds.top + bounds.height - 3.f;
    return sf::FloatRect(feetX, feetY, feetWidth, 3.f);
}

// Moe Collision Bounds
sf::FloatRect Player::getCollisionBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (direction == 1) { // facing right
        bounds.left += bounds.width * 0.3f;
    } else { // facing left
        bounds.left += bounds.width * 0.2f;
    }

    bounds.width *= 0.5f;
    bounds.top += bounds.height * 0.1f;
    bounds.height *= 0.9f;

    return bounds;
}

// Moe Positioning
void Player::setPositionY(float y) {
    sf::Vector2f pos = sprite.getPosition();
    sprite.setPosition(pos.x, y);
    velocity.y = 0.f; // stop falling
}

// Moe Ground Check
void Player::setOnGround(bool grounded) {
    isOnGround = grounded;
}

// Moe Velocity
sf::Vector2f Player::getVelocity() const {
    return velocity;
}

// Moe Vertical Velocity
void Player::cancelVerticalVelocity() {
    velocity.y = 0.f;
}

// Moe Positioning
void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}
sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}


// Moe Global Bounds
sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}


// Key Management
void Player::removeKey() {
    has_key = false;
}