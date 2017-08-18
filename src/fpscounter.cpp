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

#include "fpscounter.h"

FPSCounter::FPSCounter()
{
    // Store pointers to the application context information
    
    //this->globals = globals;
    target  = globals->window;
    
    // Set up handles
    handles.UsingTimer  = true;
    handles.TimerTime   = 1000;
    handles.UsingTick   = true;
    
    // SDL Timer
    //timer = SDL_AddTimer(1000, UpdateFPS, (void*)this);
    
    // Load the text object used to render
    text = new Text("FPS: ");
    
    // Make sure the uninitialized texture doesnt get deleted
    isTextureUsed = false;
    
    // Update the texture
    Update();
    
}

FPSCounter::~FPSCounter()
{
    delete text;
    SDL_RemoveTimer(timer);
}

void FPSCounter::Draw()
{
    text->Draw();
}

void FPSCounter::Update()
{
    globals->shouldRefresh = true;

    text->text = "FPS: " + std::to_string(frameCounter);
    text->Update();
    
    text->Position.x = text->texture->w/2.0;
    text->Position.y = (target->h)-(text->texture->h/2.0);
}

void FPSCounter::OnTimedTick()
{
    Update();
    frameCounter = 0;
}

void FPSCounter::OnTick()
{
    //frameCounter++;
}


Uint32 FPSCounter::UpdateFPS(Uint32 interval, void* param)
{
    // Get pointer to this class
    FPSCounter* myobj = (FPSCounter*)param;
    printf("locking mutex worked....");printf("locking mutex worked....");
    printf("locking mutex worked....");
    // Update fps text and counter safely
    if (SDL_LockMutex(myobj->mutex) == 0)
    {
        printf("locking mutex worked....");
    }else { 
        printf("locking mutex failed....");
    }
    myobj->Update();
    myobj->frameCounter = 0;
    SDL_UnlockMutex(myobj->mutex);
}



