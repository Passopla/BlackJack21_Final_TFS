// main.cpp
#include "graphics.h"
#include "game.h"
#include "cards.h"
#include <iostream>

enum class ApplicationState 
{
    START_SCREEN,
    PLAYING_GAME
};

// This function handles all the drawing for the start screen.
void drawStartScreen(Graphics& graphics, SDL_Texture* buttonTexture, bool isMouseDown)
{
    // A simple title
    graphics.drawText("Mdubulo's Blackjack!", 380, 220, 36, { 255, 255, 255, 255 });

    // Basic rules
    graphics.drawText("Rules:", 470, 300, 24, { 255, 255, 255, 255 });
    graphics.drawText("- Get as close to 21 as possible without going over.", 220, 340, 20, { 255, 255, 255, 255 });
    graphics.drawText("- Aces are 1 or 11. Face cards are 10.", 220, 370, 20, { 255, 255, 255, 255 });
    graphics.drawText("- Press 'H' to Hit, 'S' to Stand, 'N' for a New Round.", 220, 400, 20, { 255, 255, 255, 255 });

    // Draw the start button
    // The source rectangle for a single button image is its full size.
    SDL_Rect srcRect = { 0, 0, 200, 75 }; // Assuming button is 200x75
    graphics.drawSprite(buttonTexture, srcRect, 412, 500); // Centered: (1024/2) - (200/2) = 412
};

int main(int argc, char* argv[])
{
    // 1. Initialize our systems
    // This one line creates the window, renderer, and initializes SDL.
    Graphics graphics;
    Game blackjackGame;

    SDL_Texture* cardDeckTexture = graphics.loadTexture("assets/cardsDeckTexture.png");
    SDL_Texture* startButtonUpTexture = graphics.loadTexture("assets/playButtonUnpressed.png");
    SDL_Texture* startButtonDownTexture = graphics.loadTexture("assets/playButtonPressed.png");

    if (cardDeckTexture == nullptr || startButtonUpTexture == nullptr || startButtonDownTexture == nullptr) 
    {
        // If loading fails, the error is already printed by loadTexture.
        return 1;
    }

    // --- State Variables ---
    ApplicationState appState = ApplicationState::START_SCREEN;
    bool running = true;
    SDL_Event event;

    // Define the clickable area for our button
    SDL_Rect startButtonRect = { 412, 500, 200, 75 };
    bool isMouseButtonDown = false;

    // --- Main Game Loop ---
    while (running)
    {
        // --- Event Handling ---
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // The input handling depends on the application state
            if (appState == ApplicationState::START_SCREEN)
            {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    SDL_Point mousePoint = { mouseX, mouseY };
                    if (SDL_PointInRect(&mousePoint, &startButtonRect)) {
                        isMouseButtonDown = true;
                    }
                }
                if (event.type == SDL_MOUSEBUTTONUP) {
                    if (isMouseButtonDown) { // Only trigger if the click started on the button
                        appState = ApplicationState::PLAYING_GAME;
                        blackjackGame.startRound(); // Start the first round NOW
                    }
                    isMouseButtonDown = false;
                }
            }
            else if (appState == ApplicationState::PLAYING_GAME)
            {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                    case SDLK_h: blackjackGame.playerHit(); break;
                    case SDLK_s: blackjackGame.playerStand(); break;
                    case SDLK_n: blackjackGame.startRound(); break;
                    case SDLK_ESCAPE: running = false; break;
                    }
                }
            }
        }

        graphics.prepareScene();

        // The drawing logic depends on the application state
        if (appState == ApplicationState::START_SCREEN)
        {
            SDL_Texture* currentButtonTexture = isMouseButtonDown ? startButtonDownTexture : startButtonUpTexture;
            drawStartScreen(graphics, currentButtonTexture, isMouseButtonDown);
        }
        else if (appState == ApplicationState::PLAYING_GAME)
        {
            blackjackGame.draw(graphics, cardDeckTexture);
        }

        graphics.presentScene();
    }

    // --- Cleanup ---
    SDL_DestroyTexture(cardDeckTexture);
    SDL_DestroyTexture(startButtonUpTexture);
    SDL_DestroyTexture(startButtonDownTexture);
    return 0;
};