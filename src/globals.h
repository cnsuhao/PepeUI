#include <string>
#include <SDL2/SDL_render.h>

// Global variable structure
struct Globals {
    SDL_Color BackgroundColor = {40,40,40,255};
    std::string WindowTitle = "Eyeyeye";
    bool shouldQuit = false;
};
