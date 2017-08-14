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

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "fontmanager.h"
#include "includes.h"
#include "globals.h"


struct EventHandles { 
    bool        ShouldDraw          = true;
    bool        UsingTick           = false;
    bool        UsingTimer          = false;
    bool        UsingKeyDown        = false;
    bool        UsingKeyUp          = false;
    bool        UsingMouseDown      = false;
    bool        UsingMouseUp        = false;
    bool        UsingMouseMotion    = false;
    bool        UsingMouseWheel     = false;
    int         TimerTime           = 1000;
    int         TimerLastTrigger    = 0;
};

class Drawable
{
public:
    Drawable() {
        //texture = GPU_CreateImage(10,10,GPU_FormatEnum::GPU_FORMAT_RGBA);
    };
    
    virtual ~Drawable() 
    {
        // Free the texture
        if (isTextureUsed) GPU_FreeImage(texture);
    };
    
    // Functions
    /* Used to draw to the screen*/
    virtual void Draw(){};
    virtual void Update(){};
    
    // Eventhandling
    EventHandles handles;
    virtual void OnTick         (){};
    virtual void OnTimedTick    (){};
    virtual void OnKeyDown      (SDL_Event* event){};
    virtual void OnKeyUp        (SDL_Event* event){};
    virtual void OnMouseDown    (SDL_Event* event){};
    virtual void OnMouseUp      (SDL_Event* event){};
    virtual void OnMouseMotion  (SDL_Event* event){};
    virtual void OnMouseWheel   (SDL_Event* event){};
    virtual void OnInputCaptured(SDL_Event* event){};
    
    // Members
    bool        isTextureUsed = true;
    GPU_Image*  texture;
    float       Opacity;
    vec2        Position;
    vec2        Size;
    SDL_Color   Color = {255, 255, 255, 255};    
    GPU_Target* target;
    GPU_Rect    srcrect = {0,0,100,100};
    GPU_Rect    rect;
    SDL_mutex*  mutex;
    const char* id;
    
    // Static members
    static Globals*    globals;
    
};


#endif // DRAWABLE_H
