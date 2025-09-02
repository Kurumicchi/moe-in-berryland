#include <SFML/Graphics.hpp>
#include "skeleton/constants.h"
#include "skeleton/Game.h"

int main()
{
    Game game("Moe in Berryland", screen_width, screen_height);
    game.start();
    return 0;
}