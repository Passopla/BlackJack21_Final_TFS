// graphics.cpp
#include "graphics.h"
#include <iostream> // For printing error messages
#include "SDL_image.h"

SDL_Texture* Graphics::loadTexture(const std::string& filePath)
{
    SDL_Texture* texture = nullptr;
    // Load the image into a temporary surface
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image " << filePath << "! IMG_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Convert the surface into a texture that the renderer can use
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture from " << filePath << "! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Free the temporary surface now that we're done with it
    SDL_FreeSurface(surface);

    return texture;
}

void Graphics::drawSprite(SDL_Texture* texture, const SDL_Rect& srcRect, int x, int y)
{
    // The destination rectangle on the screen
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    // The destination width and height are the same as the source's
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    // Copy the specific part of the texture (srcRect) to the renderer 
    // at the destination location (destRect).
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

// Constructor Implementation
Graphics::Graphics()
{
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1); // Exit if we can't initialize SDL
    }

    // Create the window
    window = SDL_CreateWindow(
        "Blackjack",                // Window title
        SDL_WINDOWPOS_CENTERED,    // Initial x position
        SDL_WINDOWPOS_CENTERED,    // Initial y position
        1024,                       // Width, in pixels
        768,                        // Height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE            // Flags
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

// Destructor Implementation
Graphics::~Graphics()
{
    // Clean up in reverse order of creation
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "SDL resources cleaned up!" << std::endl;
}

void Graphics::prepareScene()
{
    // Set the draw color to our background color (e.g., a dark green)
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // R, G, B, A
    // Clear the entire screen to that color
    SDL_RenderClear(renderer);
}

void Graphics::presentScene()
{
    // Swap the back buffer with the front buffer to display the rendered scene
    SDL_RenderPresent(renderer);
}