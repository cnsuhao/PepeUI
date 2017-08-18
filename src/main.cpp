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

#define DEBUG

// System includes
#include "includes.h"

// Local includes
#include "console.h"
#include "form.h"
#include "fpscounter.h"

// Global variables
Globals* globals;

// Manager includes
#include "eventmanager.h"
#include "fontmanager.h"
#include "drawablemanager.h"
#include "mainprogram.h"

int main(int argc, char **argv) {
    // Store all globals here and fill the pointers
    Globals globalsobj;
    globals = &globalsobj;
    Drawable::globals = globals;
    
    // Create a window
    Form form = Form(globals);
    
    // Create resource managers
    FontManager     fontmanager;
    DrawableManager drawablemanager;
    
    // Create main program object and load it
    MainProgram     program;
    
    // Initialize and update event manager after load   
    EventManager::InitEventManager(DrawableManager::GetDrawableMap());
    
    // Main loop
    while(!globalsobj.shouldQuit) {
        // Handle input
        EventManager::TriggerEvents();
        

        // Trigger Tick() of the main program
        program.Tick();
        
        // Trigger OnTick(), OnTimedTick() and Draw() appropriately
        EventManager::TriggerTickFunctions(form.window);
        
        // Swap backbuffers
        if(globalsobj.shouldRefresh)
            GPU_Flip(form.window);

        globalsobj.shouldRefresh = false;
    }
    
    return 0;
}
