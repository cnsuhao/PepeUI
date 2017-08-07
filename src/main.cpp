#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>

int main(int argc, char **argv) {
    std::cout << "SDL2 Attempting initialization." << std::endl;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
       std::cout << "SDL2 failed with error: " << SDL_GetError() << std::endl;
       return -1;
    }
    std::cout << "SDL2 Initialized successfully!" << std::endl;
    
    
    
    
    std::cout << "Quitting SDL2." << std::endl;
    SDL_Quit();
    return 0;
}
