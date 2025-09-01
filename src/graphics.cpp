// graphics.cpp
#include "graphics.h"
#include "SDL_image.h"
#include <iostream> // For printing error messages

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
        SDL_WINDOWPOS_UNDEFINED,    // Initial x position
        SDL_WINDOWPOS_UNDEFINED,    // Initial y position
        1024,                       // Width, in pixels
        768,                        // Height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE         // Flags
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

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        // Clean up other things before exiting
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // Load the font
    font = TTF_OpenFont("assets/Welbut__.ttf",24); // 24 is the font size
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        // Clean up before exiting
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

// Destructor Implementation
Graphics::~Graphics()
{
    // Clean up in reverse order of creation
    TTF_CloseFont(font); // Free the font
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "SDL resources cleaned up!" << std::endl;
}

void Graphics::prepareScene()
{
    // Set the draw color to our background color (e.g., a dark green)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // R, G, B, A
    // Clear the entire screen to that color
    SDL_RenderClear(renderer);
}

void Graphics::presentScene()
{
    // Swap the back buffer with the front buffer to display the rendered scene
    SDL_RenderPresent(renderer);
}

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
    SDL_Rect destRect = { x, y, srcRect.w, srcRect.h };

    // Copy the specific part of the texture (srcRect) to the renderer 
    // at the destination location (destRect).
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void Graphics::drawText(const std::string& text, int x, int y, int fontSize, SDL_Color color)
{
    // This process is very similar to loading an image:
    // 1. Render the text to a temporary surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) 
    {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return; // Don't crash if text fails to render
    }

    // 2. Convert the surface to a texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) 
    {
        std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface); // Still need to free the surface
        return;
    }

    // 3. Get the dimensions of the texture and draw it
    SDL_Rect destRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

    // 4. IMPORTANT: Clean up the temporary resources
    // We create and destroy the texture every frame. This is necessary because
    // the text (like the score) can change from one frame to the next.
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Graphics::getTextSize(const std::string& text, int* width, int* height) const
{
    // Make sure our font is valid before using it
    if (font == nullptr)
    {
        if (width) *width = 0;
        if (height) *height = 0;
        return;
    }

    TTF_SizeText(font, text.c_str(), width, height);
}