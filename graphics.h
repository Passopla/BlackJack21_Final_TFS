#pragma once

// We must include the main SDL header here
#include "SDL.h"
#include <string>

class Graphics
{
public:
    // Constructor: This runs when we create a Graphics object.
    // It will initialize SDL, create the window, and create the renderer.
    Graphics();

    // Destructor: This runs when the Graphics object is destroyed.
    // It will clean up the renderer, the window, and shut down SDL.
    ~Graphics();

    // A function to prepare the scene for drawing (i.e., clear the screen)
    void prepareScene();

    // A function to present the final rendered scene to the screen
    void presentScene();

    SDL_Texture* loadTexture(const std::string& filePath);
    void drawSprite(SDL_Texture* texture, const SDL_Rect& srcRect, int x, int y);

private:
    // These are pointers to the main SDL window and renderer.
    // We make them private so only our Graphics class can touch them directly.
    SDL_Window* window;
    SDL_Renderer* renderer;
};
