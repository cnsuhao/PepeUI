#include "form.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Globals globals;
    Form* form = new Form(&globals);

    // Main while loop
    while(!globals.shouldQuit) {
        // Process input events
        SDL_Event event;
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
            case SDL_KEYDOWN:
                printf( "Key press detected\n" );
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym==SDLK_ESCAPE)
                    globals.shouldQuit=true;
                break;
            case SDL_QUIT:
                globals.shouldQuit = true;
                break;
            }
        }
        
        // Render
        GPU_ClearColor(form->window,globals.BackgroundColor);
        GPU_Flip(form->window);
    }
    
    delete form;
    return 0;
}
