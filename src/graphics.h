#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <string> // Needed for the string filepath

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void prepareScene();
    void presentScene();

    // NEW FUNCTION: Loads an image from a file into an SDL_Texture
    SDL_Texture* loadTexture(const std::string& filePath);

    // NEW FUNCTION: Draws a texture to the screen at a specific x, y coordinate
    void drawSprite(SDL_Texture* texture, const SDL_Rect& srcRect, int x, int y);
    void drawText(const std::string& text, int x, int y, int fontSize, SDL_Color color);
    void getTextSize(const std::string& text, int* width, int* height) const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
};