// game.h
#pragma once

#include "player.h"
#include "dealer.h"
#include "deck.h"

// Forward declaration for Graphics class to avoid including the full header
class Graphics;
// We need SDL_Texture for the draw method parameter
struct SDL_Texture;

// Defines the current state of the game round
enum class GameState {
    PLAYER_TURN,
    DEALER_TURN,
    GAME_OVER
};

class Game
{
public:
    Game();

    void startRound();    // Replaces the old play() logic for starting a game
    void playerHit();     // Handles the player's "hit" action
    void playerStand();   // Handles the player's "stand" action
    GameState getGameState() const { return gameState; }

    // The main draw function for the game
    void draw(Graphics& graphics, SDL_Texture* cardSpriteSheet);

private:
    // This is the private helper function the compiler can't find
    void determineWinner();
    void checkForBlackjack();

    // These are the private member variables the compiler can't find
    Player player;
    Dealer dealer;
    Deck deck;
    GameState gameState;
    std::string winnerMessage;
};