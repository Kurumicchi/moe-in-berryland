#include "Winning_State.h"
#include "constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

Winning_State::Winning_State() {
    if (!bgTexture.loadFromFile("assets/Import/Moewin.png")) {
        std::cerr << "Failed to load winning background image\n";
    }
    background.setTexture(bgTexture);
    background.setScale(
        static_cast<float>(screen_width) / bgTexture.getSize().x,
        static_cast<float>(screen_height) / bgTexture.getSize().y
    );
}


void Winning_State::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) {
        exit(0); // pressing Z exits game
    }
}

void Winning_State::update() {
    // No update logic needed for the winning state
}

void Winning_State::render(sf::RenderTarget& target) {
    target.setView(target.getDefaultView());
    target.draw(background);
}

int Winning_State::get_next_state() {
    return WINNING_STATE; // stay in winning screen
}