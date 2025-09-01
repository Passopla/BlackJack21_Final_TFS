// cards.h
#pragma once

#include "SDL.h" // Needed for SDL_Rect
#include <string>

// Forward declare Graphics class to avoid circular includes
class Graphics;

enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { CLUBS = 0, DIAMONDS, HEARTS, SPADES };

// --- We are changing the Card from a struct to a class ---
class Card
{
public:
    // Constructor: Initializes a card with a specific rank and suit
    Card(Rank rank, Suit suit);

    // The draw method: tells the card to draw itself to a specific location
    void draw(Graphics& graphics, SDL_Texture* spriteSheet, int x, int y) const;

    Rank getRank() const;
    Suit getSuit() const;

private:
    Rank rank;
    Suit suit;
    
    // Each card will now store its own source rectangle from the sprite sheet
    SDL_Rect srcRect; 
};

// The text name arrays are unchanged
extern const char* SUIT_NAMES[];
extern const char* RANK_NAMES[];