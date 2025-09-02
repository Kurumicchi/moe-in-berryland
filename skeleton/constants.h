#pragma once

/*
 * In this file we define some global constants.
 *
 * Please note that the problem with global variables
 * is that anyone can change them whenever which makes
 * it extremely hard to reason about your code. But for
 * constants, this is not a problem since we cannot
 * change them, and therefore they stay the same during
 * the entire execution of the program.
 */

/*
 * define the size of the window.
 */

// Aspect Ratio 4:3
int const screen_width  { 1024 };
int const screen_height { 768 };

/*
 * define how many fps we want our program to run in.
 */
double const fps { 60.0 };

// Game state IDs
const int MENU_STATE  = 0;
const int GAME_STATE  = 1;
const int WINNING_STATE = 2;