/*
 * Copyright (c) 2017 Anas Youssef Idiab candfa2660@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "form.h"

Form::Form(Globals* globals)
{
    // Store a pointer to the global variables
    this->globals = globals;
    
    // SDL_gpu debugging
#ifdef DEBUG
    GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
#endif // DEBUG
    
    // Create window
    window = GPU_Init(1200,720,GPU_DEFAULT_INIT_FLAGS);
    globals->window = window;
    
    // Start text input 
    SDL_StartTextInput();
    
    // Initialize SDL_ttf
    if(!TTF_WasInit() && TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
    
    // SDL window options
    {
        // Obtain SDL window from gpu window
        SDL_Window* sdlwindow = SDL_GetWindowFromID(window->context->windowID);
        
        // Set window title
        SDL_SetWindowTitle(sdlwindow, globals->WindowTitle.c_str());
        
        // Set resizable
        SDL_SetWindowResizable(sdlwindow, SDL_TRUE);
    }
}

Form::~Form()
{
    // Delete target memory
    GPU_FreeTarget(window);
    
    // Deinitialize SDL_ttf
    TTF_Quit();
    
    // Deinitialize SDL2 and SDL_gpu
    GPU_Quit();    
}
