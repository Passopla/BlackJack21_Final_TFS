// player.h
#pragma once
#include <vector>
#include "cards.h"

class Player 
{
private:
    std::vector<Card> hand; // Declare the hand vector

public:
    Player();

    void addCard(const Card& card);
    void clearHand();
    int getHandValue() const;
    const std::vector<Card>& getHand() const; // Declare the getHand function
};