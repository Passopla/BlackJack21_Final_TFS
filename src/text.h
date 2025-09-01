// text.h
#pragma once

// Forward declarations to avoid circular dependencies, though including is also fine here.
class Player;
class Dealer;

/**
 * @brief Clears the console screen.
 * Works on both Windows and POSIX-compliant systems (Linux, macOS).
 */
void clearScreen();

/**
 * @brief Displays the current hands of the player and the dealer.
 * @param player The player object.
 * @param dealer The dealer object.
 * @param showAllCards If true, all of the dealer's cards are shown.
 *                     If false, the dealer's first card is shown as hidden.
 */
void displayHands(const Player& player, const Dealer& dealer, bool showAllCards);