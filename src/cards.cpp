// cards.cpp
#include "cards.h"
#include "graphics.h" // We need the full definition of Graphics here

// Define constants for the dimensions of a single card on the sprite sheet
const int CARD_WIDTH = 62;
const int CARD_HEIGHT = 84;

// --- Constructor Implementation ---
Card::Card(Rank rank, Suit suit)
{
    // Store the rank and suit
    this->rank = rank;
    this->suit = suit;

    // Calculate the source rectangle on the sprite sheet
    // The X position is determined by the rank.
    // The Y position is determined by the suit.
    srcRect.x = (rank - 1) * CARD_WIDTH; // We do rank - 1 because ACE is 1, but array/pixel coords are 0-indexed
    srcRect.y = suit * CARD_HEIGHT;      // Suit is already 0-indexed (CLUBS = 0)
    srcRect.w = CARD_WIDTH;
    srcRect.h = CARD_HEIGHT;
}

// --- Draw Method Implementation ---
void Card::draw(Graphics& graphics, SDL_Texture* spriteSheet, int x, int y) const
{
    // Tell the graphics object to draw the sprite defined by our source rectangle
    // at the given x, y screen coordinates.
    graphics.drawSprite(spriteSheet, srcRect, x, y);
}

Rank Card::getRank() const
{
    return rank;
}

Suit Card::getSuit() const
{
    return suit;
}

// The text name arrays are unchanged and still live here.
const char* SUIT_NAMES[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
const char* RANK_NAMES[] = {
    "N/A", "Ace", "Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"
};