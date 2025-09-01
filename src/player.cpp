// player.cpp
#include "player.h"

Player::Player() {}
// add a card to the player's hand. same as dealer
void Player::addCard(const Card& card) 
{
    hand.push_back(card);
}

void Player::clearHand() 
{
    hand.clear();
}
// calculate player hand. same as dealer
int Player::getHandValue() const // (and int Dealer::getHandValue() const)
{
    int totalValue = 0;
    int numAces = 0; // Use a counter for aces instead of a boolean flag

    for (const Card& card : hand)
    {
        int rankValue = card.getRank();

        if (rankValue >= JACK) // JACK, QUEEN, KING are 11, 12, 13
        {
            totalValue += 10;
        }
        else if (rankValue == ACE)
        {
            numAces++;
            totalValue += 11; // Initially count all Aces as 11
        }
        else
        {
            totalValue += rankValue; // For cards 2-10
        }
    }

    // After summing everything, adjust for Aces if the total is over 21
    // This loop will correctly handle multiple Aces.
    while (totalValue > 21 && numAces > 0)
    {
        totalValue -= 10; // Change an Ace from 11 to 1
        numAces--;
    }

    return totalValue;
}

const std::vector<Card>& Player::getHand() const
{
    return hand;
}
