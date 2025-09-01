// deck.cpp
#include "deck.h"
#include <random>
#include <cstdlib>
#include <ctime>

Deck::Deck() {
// initialize deck with all rank and suit combinations
	for (int suit = CLUBS; suit <= SPADES; ++suit)
	{
		for (int rank = ACE; rank <= KING; ++rank)
		{
			cards.push_back({ static_cast<Rank>(rank), static_cast<Suit>(suit) });
		}
	}
}

void Deck::shuffle()
{
	// Seed the random number generator
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Create a random number engine
	std::default_random_engine rng(std::rand());

	// Shuffle the deck with std::shuffle
	std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::dealCard()
{
	// Remove and return the last card from the deck
	Card dealtCard = cards.back();
	cards.pop_back();
	return dealtCard;
}
