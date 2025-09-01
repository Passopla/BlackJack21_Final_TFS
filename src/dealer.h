// dealer.h
#pragma once
#include <vector>
#include "cards.h"

class Dealer
{
private:
	std::vector<Card> hand;

public:
	Dealer();

	void addCard(const Card& card);
	void clearHand();
	int getHandValue() const;
	const std::vector<Card>& getHand() const; // Declare the getHand function
};