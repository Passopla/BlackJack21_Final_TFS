// text.cpp

#include "text.h"   // For the declarations of clearScreen() and displayHands()
#include "player.h" // Needed to understand the Player class
#include "dealer.h" // Needed to understand the Dealer class
#include "cards.h"  // For the Card struct, enums, and the extern arrays RANK_NAMES/SUIT_NAMES
#include <iostream> // For std::cout and std::endl
#include <cstdlib>  // For std::system

/**
 * @brief Clears the console screen.
 */
void clearScreen()
{
#ifdef _WIN32
    std::system("CLS"); // Command for Windows
#else
    std::system("clear"); // Command for Linux/macOS
#endif
}

/**
 * @brief Displays the current hands of the player and the dealer.
 */
void displayHands(const Player& player, const Dealer& dealer, bool showAllCards)
{
    clearScreen();

    // --- Display Player's Hand ---
    std::cout << "Player's Hand: ";
    // Loop through each card in the player's hand and print its string name
    for (const auto& card : player.getHand())
    {
        // Access the global arrays using the enum values as indices
        std::cout << "(" << RANK_NAMES[card.getRank()] << ", " << SUIT_NAMES[card.getSuit()] << ") ";
    }
    std::cout << "(Total: " << player.getHandValue() << ")" << std::endl;


    // --- Display Dealer's Hand ---
    std::cout << "Dealer's Hand: ";
    if (showAllCards)
    {
        // If it's the end of the round, show all the dealer's cards
        for (const auto& card : dealer.getHand())
        {
            std::cout << "(" << RANK_NAMES[card.getRank()] << ", " << SUIT_NAMES[card.getSuit()] << ") ";
        }
        std::cout << "(Total: " << dealer.getHandValue() << ")" << std::endl;
    }
    else
    {
        // During the player's turn, show the dealer's first card (up-card) and hide the second
        const auto& hand = dealer.getHand();
        if (!hand.empty())
        {
            // Show the first card
            const auto& firstCard = hand[0];
            std::cout << "(" << RANK_NAMES[firstCard.getRank()] << ", " << SUIT_NAMES[firstCard.getSuit()] << ") ";

            // Show a placeholder for the second (and any subsequent) card
            if (hand.size() > 1)
            {
                std::cout << "(Hidden, Hidden) ";
            }
        }
        // Don't reveal the total value
        std::cout << "(Total: ?)" << std::endl;
    }

    std::cout << std::endl; // Add an extra newline for better readability between turns
}