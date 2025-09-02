#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


class Platform;
class Player {
public:
    Player();

    void handleInput();
    void draw(sf::RenderTarget& target);

    sf::FloatRect getGlobalBounds() const;
    void setPositionY(float y);
    void setOnGround(bool grounded);
    
    sf::Vector2f getVelocity() const;
    void cancelVerticalVelocity();
    
    void applyPhysics();
    void move(const std::vector<Platform>& platforms);
    void updateAnimation();

    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();

    sf::FloatRect getFeetHitbox() const;
    sf::FloatRect getCollisionBounds() const;

    enum class AnimationState {
        Idle,
        Walk,
        Jump,
    };

    AnimationState currentAnim;

    sf::FloatRect getBounds() const;

    bool hasKey() const { return has_key; }
    void collectKey() { has_key = true; }
    void resetKey() { has_key = false; }
    void removeKey();

private:
    // Idle anim
    std::vector<std::shared_ptr<sf::Texture>> idleFrames;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

    // Walk anim
    std::vector<std::shared_ptr<sf::Texture>> walkFrames;
    bool isMoving;

    // Jump anim
    std::vector<std::shared_ptr<sf::Texture>> jumpFrames;
    bool wasJumping;

    // Animation tracking
    int currentFrame;
    float frameTimer;
    float frameDelay;

    // Gravity & Ground Checking
    sf::Vector2f velocity;
    bool isOnGround;

    // Player direction
    int direction; // 1 for right, -1 for left

    bool has_key = false;
};