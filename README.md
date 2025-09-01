# C++ Blackjack with SDL2

This is a complete, fully playable Blackjack (21) card game built from the ground up in C++. It was developed as a comprehensive University project at Toronto Film School to learn the fundamentals of game architecture, object-oriented programming, and graphical rendering with the SDL2 library.

<img width="1026" height="800" alt="image" src="https://github.com/user-attachments/assets/26665962-d179-41d6-b987-3846093cf0f5" />

<img width="1026" height="800" alt="image" src="https://github.com/user-attachments/assets/075343e0-a5d5-48be-8436-01b155f013ae" />

<img width="1026" height="800" alt="image" src="https://github.com/user-attachments/assets/18c56434-463c-49ef-917f-734d674687ad" />

<img width="1026" height="800" alt="image" src="https://github.com/user-attachments/assets/3cdc2815-f077-40ea-b5d1-2e1e50eb420a" />

---

## Features

*   **Start Screen:** A welcoming start screen with a play button and game rules.
*   **Full Graphical Gameplay:** All game elements are rendered graphically using a sprite sheet.
*   **Complete Game Logic:** Implements all standard Blackjack rules:
    *   Player can Hit or Stand.
    *   Dealer follows standard "hit on 16, stand on 17" rules.
    *   Correctly handles Busts, Natural Blackjacks, and Push (tie) conditions.
*   **Dynamic UI:** The interface displays real-time scores and game state messages (e.g., "Player Busts!", "Game Over!").
*   **State Management:** A robust state machine handles the flow between the start menu and the main game.

## Technologies Used

*   **Language:** C++
*   **Graphics & Input:** SDL2
*   **Image Loading:** SDL_image (for loading PNG assets)
*   **Font Rendering:** SDL_ttf (for displaying text)
*   **IDE:** Visual Studio 2022

## How to Build and Run

This project is configured as a Visual Studio solution.

#### 1. Dependencies
The required SDL2, SDL_image, and SDL_ttf libraries are included in the `/libs` directory. The Visual Studio project is pre-configured to look for headers and libraries in this location.

#### 2. Building
Simply open the `.sln` file in Visual Studio and build the solution for the x64 platform.

#### 3. Running
To run the compiled `.exe` from the `x64/Debug` folder, you must first copy the required runtime files into that folder:
*   Copy the entire `/assets` folder.
*   Copy all of the `.dll` files from the `/libs` subdirectories (e.g., `SDL2.dll`, `SDL2_image.dll`, `libpng16-16.dll`, etc.).

## Acknowledgments

*   Card sprite sheet assets provided by [yaomonl](https://yaomon.itch.io/playing-cards).
*   Wellbutrin font asset provided by [Apostrophic Labs]([https://yaomon.itch.io/playing-cards](https://yaomon.itch.io/playing-cards).
*   Play Button sprite sheet assets provided by [SlyFoxStudios](https://slyfox-studios.itch.io/buttons-pack).
