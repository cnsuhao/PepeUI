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

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "includes.h"
#include "fpscounter.h"

namespace EventManager {
    // Functions
    void InitEventManager(std::map<const char*, Drawable*>* drawables);
    void UpdateHandles();
    void TriggerTickFunctions ();
    void TriggerEvents();
    
    // Variables
    std::map<const char*, std::vector<Drawable*>>   eventhandles;
    std::map<const char*, Drawable*>*               drawables;
    
    
    
    void InitEventManager(std::map<const char*, Drawable*>* drawables) {
        EventManager::drawables     = drawables;
        eventhandles                = std::map<const char*, std::vector<Drawable*>>();
        eventhandles["KeyDown"]     = std::vector<Drawable*>();
        eventhandles["KeyUp"]       = std::vector<Drawable*>();
        eventhandles["MouseDown"]   = std::vector<Drawable*>();
        eventhandles["MouseUp"]     = std::vector<Drawable*>();
        eventhandles["MouseMotion"] = std::vector<Drawable*>();
        eventhandles["MouseWheel"]  = std::vector<Drawable*>();
        UpdateHandles();
    }
    
    void UpdateHandles() {
        
        // Clear handles
        eventhandles["KeyDown"].clear();
        eventhandles["KeyUp"].clear();
        eventhandles["MouseDown"].clear();
        eventhandles["MouseUp"].clear();
        eventhandles["MouseMotion"].clear();
        eventhandles["MouseWheel"].clear();
        
        // Go through all drawables
        for (auto drawable : *drawables) {
            // Fill drawables with their ID's
            drawable.second->id = drawable.first;
            
            // Store event handles
            if (drawable.second->handles.UsingKeyDown)
                eventhandles["KeyDown"].push_back(drawable.second);
            if (drawable.second->handles.UsingKeyUp)
                eventhandles["KeyUp"].push_back(drawable.second);
            if (drawable.second->handles.UsingMouseDown)
                eventhandles["MouseDown"].push_back(drawable.second);
            if (drawable.second->handles.UsingMouseUp)
                eventhandles["MouseUp"].push_back(drawable.second);
            if (drawable.second->handles.UsingMouseMotion)
                eventhandles["MouseMotion"].push_back(drawable.second);
            if (drawable.second->handles.UsingMouseWheel)
                eventhandles["MouseWheel"].push_back(drawable.second);
        }
    }
    
    void TriggerTickFunctions (GPU_Target* window) {
        
        // Update and render all drawables
        for (auto drawable : *drawables) {
            // Trigger tick functions
            drawable.second->OnTick();
            
            // Check if using timed tick 
            if (drawable.second->handles.UsingTimer) {
                // Check if appropriate time has passed
                if (drawable.second->handles.TimerTime < SDL_GetTicks() - drawable.second->handles.TimerLastTrigger) {
                    // Trigger timer tick and store trigger time
                    drawable.second->OnTimedTick();
                    drawable.second->handles.TimerLastTrigger = SDL_GetTicks();
                }
            }


            
            
        }
        
        if(globals->shouldRefresh) {
            // Clear backbuffer
            GPU_ClearColor(window, globals->BackgroundColor);
            // Add frame to fps counter
            //(FPSCounter*)((drawables*)["fpscounter"])->frameCounter++;
            for (auto drawable : *drawables) {                
                // Render current drawable
                drawable.second->Draw();
            }
        }
        
    }
    
    void TriggerEvents() {
        // Process input events
        SDL_Event event;
        
        while( SDL_PollEvent( &event ) ){
            if (globals->CaptureStack.size() > 0) {
                (*drawables)[globals->CaptureStack.back().
                drawableID]->OnInputCaptured(&event);
                switch( event.type ){
                case SDL_KEYUP:
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                         globals->CaptureStack.pop_back();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (!globals->CaptureStack.back().mouseCaptured) {
                        for (auto drawable : eventhandles["MouseDown"]) {
                            drawable->OnMouseDown(&event);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (!globals->CaptureStack.back().mouseCaptured) {
                        for (auto drawable : eventhandles["MouseUp"]) {
                            drawable->OnMouseUp(&event);
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (!globals->CaptureStack.back().mouseCaptured) {
                        for (auto drawable : eventhandles["MouseMotion"]) {
                            drawable->OnMouseMotion(&event);
                        }
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    if (!globals->CaptureStack.back().mouseCaptured) {
                        for (auto drawable : eventhandles["MouseWheel"]) {
                            drawable->OnMouseWheel(&event);
                        }
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        GPU_SetWindowResolution(event.window.data1, event.window.data2);
                    }
                    break;
                case SDL_QUIT:
                    globals->shouldQuit = true;
                    break;
                }
            } else {
                switch( event.type ){
                case SDL_KEYDOWN:
                    for (auto drawable : eventhandles["KeyDown"]) {
                        drawable->OnKeyDown(&event);
                    }
                    break;
                case SDL_KEYUP:
                    for (auto drawable : eventhandles["KeyUp"]) {
                        drawable->OnKeyUp(&event);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (auto drawable : eventhandles["MouseDown"]) {
                        drawable->OnMouseDown(&event);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    for (auto drawable : eventhandles["MouseUp"]) {
                        drawable->OnMouseUp(&event);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    for (auto drawable : eventhandles["MouseMotion"]) {
                        drawable->OnMouseMotion(&event);
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    for (auto drawable : eventhandles["MouseWheel"]) {
                        drawable->OnMouseWheel(&event);
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        GPU_SetWindowResolution(event.window.data1, event.window.data2);
                    }
                    break;
                case SDL_QUIT:
                    globals->shouldQuit = true;
                    break;
                }
            }
        }
        
    }
}


#endif // EVENTMANAGER_H
