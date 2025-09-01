// deck.h
#pragma once
#include <vector>
#include "cards.h"

class Deck 
{
private:
	std::vector<Card> cards;

public:
	Deck();

	void shuffle();
	Card dealCard();
};

