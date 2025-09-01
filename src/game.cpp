// game.cpp
#include "game.h"
#include "graphics.h"
#include <iostream> // For console debug messages
#include <string>

Game::Game() : deck(), gameState(GameState::GAME_OVER), winnerMessage("")
{
    // The constructor is now very simple.
}

void Game::startRound()
{
    // 1. Prepare for a new round by clearing everything.
    deck = Deck();
    deck.shuffle();
    player.clearHand();
    dealer.clearHand();
    winnerMessage = "";

    // 2. Deal the initial cards.
    player.addCard(deck.dealCard());
    dealer.addCard(deck.dealCard());
    player.addCard(deck.dealCard());
    dealer.addCard(deck.dealCard());

    std::cout << "--- New Round Started ---" << std::endl;

    // 3. IMPORTANT: Assume it is the player's turn now.
    gameState = GameState::PLAYER_TURN;

    // 4. NOW, check for a Blackjack. If one is found, this function
    //    will override the state to GAME_OVER.
    checkForBlackjack();
}

void Game::playerHit()
{
    // Can only hit during the player's turn
    if (gameState == GameState::PLAYER_TURN)
    {
        player.addCard(deck.dealCard());
        std::cout << "Player hits. New total: " << player.getHandValue() << std::endl;

        // Check for bust first
        if (player.getHandValue() > 21)
        {
            std::cout << "Player busts!" << std::endl;
            determineWinner();
        }
        // --- NEW LOGIC ---
        // If not a bust, check if the player has exactly 21.
        else if (player.getHandValue() == 21)
        {
            std::cout << "Player has 21! Automatically standing." << std::endl;
            // The player's turn is over. Start the dealer's turn.
            playerStand();
        }
    }
}

void Game::playerStand()
{
    // Can only stand during the player's turn
    if (gameState == GameState::PLAYER_TURN)
    {
        std::cout << "Player stands." << std::endl;
        gameState = GameState::DEALER_TURN;

        // --- Dealer's Turn Logic ---
        while (dealer.getHandValue() < 17)
        {
            dealer.addCard(deck.dealCard());
            std::cout << "Dealer hits. New total: " << dealer.getHandValue() << std::endl;
        }

        determineWinner();
    }
}

void Game::determineWinner()
{
    gameState = GameState::GAME_OVER;

    int playerTotal = player.getHandValue();
    int dealerTotal = dealer.getHandValue();

    // We can reuse our old console logic for printing the result for now
    if (playerTotal > 21) {
        winnerMessage = "Player Busts. Dealer Wins!";
    }
    else if (dealerTotal > 21) {
        winnerMessage = "Dealer Busts. Player Wins!";
    }
    else if (playerTotal > dealerTotal) {
        winnerMessage = "Player Wins!";
    }
    else if (dealerTotal > playerTotal) {
        winnerMessage = "Dealer Wins!";
    }
    else {
        winnerMessage = "It's a Push (Tie)!";
    }

    std::cout << winnerMessage << std::endl;
}

void Game::checkForBlackjack()
{
    bool playerHasBlackjack = (player.getHandValue() == 21 && player.getHand().size() == 2);
    bool dealerHasBlackjack = (dealer.getHandValue() == 21 && dealer.getHand().size() == 2);

    if (playerHasBlackjack || dealerHasBlackjack)
    {
        // If anyone has a Blackjack, the game is immediately over.
        // Our existing determineWinner() function correctly handles the win/loss/tie logic.
        std::cout << "Blackjack detected!" << std::endl;
        determineWinner();
    }
    // Otherwise, do nothing and let the game proceed to the player's turn.
}

void Game::draw(Graphics& graphics, SDL_Texture* cardSpriteSheet)
{
    // Define constants for card and window dimensions
    const int CARD_WIDTH = 73;
    const int SPACING = 90; // The space from the start of one card to the next
    const int WINDOW_WIDTH = 1024;

    // --- Draw Player's Hand (Centered) ---
    const int playerNumCards = static_cast<int>(player.getHand().size());
    const int playerHandWidth = (playerNumCards - 1) * SPACING + CARD_WIDTH;
    int playerCardX = (WINDOW_WIDTH / 2) - (playerHandWidth / 2); // Calculated start X
    const int playerCardY = 450;
    for (const Card& card : player.getHand()) {
        card.draw(graphics, cardSpriteSheet, playerCardX, playerCardY);
        playerCardX += SPACING; // Move to the next card position
    }

    // --- Draw Dealer's Hand (Centered) ---
    const int dealerNumCards = static_cast<int>(dealer.getHand().size());
    const int dealerHandWidth = (dealerNumCards - 1) * SPACING + CARD_WIDTH;
    int dealerCardX = (WINDOW_WIDTH / 2) - (dealerHandWidth / 2); // Calculated start X
    const int dealerCardY = 50;

    const auto& dealerHand = dealer.getHand();
    for (size_t i = 0; i < dealerHand.size(); ++i)
    {
        if (i == 1 && gameState == GameState::PLAYER_TURN)
        {
            // We'll draw a card back later. For now, we still just skip it.
        }
        else
        {
            dealerHand[i].draw(graphics, cardSpriteSheet, dealerCardX, dealerCardY);
        }
        dealerCardX += SPACING;
    }

    // --- Draw All Text ---
    SDL_Color white = { 255, 255, 255, 255 };

    // Player's Score
    std::string playerTotalStr = "Player Total: " + std::to_string(player.getHandValue());
    graphics.drawText(playerTotalStr, 415, 600, 24, white);

    // Dealer's Score
    if (gameState != GameState::PLAYER_TURN) {
        std::string dealerTotalStr = "Dealer Total: " + std::to_string(dealer.getHandValue());
        graphics.drawText(dealerTotalStr, 415, 200, 24, white);
    }
    else {
        graphics.drawText("Dealer's Hand", 415, 200, 24, white);
    }

    // Instructions
    graphics.drawText("Controls: 'H' (Hit), 'S' (Stand), 'N' (New Round)", 215, 700, 20, white);

    // Game Over and Winner Message
    if (gameState == GameState::GAME_OVER && !winnerMessage.empty())
    {
        int textW, textH; // Variables to hold the size of our text

        // 1. Measure the winner message
        graphics.getTextSize(winnerMessage, &textW, &textH);
        // 2. Calculate the centered X coordinate
        int centeredWinnerX = (WINDOW_WIDTH / 2) - (textW / 2);
        // 3. Draw the text at the calculated position
        graphics.drawText(winnerMessage, centeredWinnerX, 320, 24, white);

        // -- Repeat the process for the "New Round" prompt --
        std::string newRoundPrompt = "Game Over! Press 'N' for New Round.";
        // 1. Measure the prompt
        graphics.getTextSize(newRoundPrompt, &textW, &textH);
        // 2. Calculate the centered X coordinate
        int centeredPromptX = (WINDOW_WIDTH / 2) - (textW / 2);
        // 3. Draw the prompt at its calculated position
        graphics.drawText(newRoundPrompt, centeredPromptX, 350, 24, white);
    }
}