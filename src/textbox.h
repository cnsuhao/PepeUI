/*
 * Copyright (c) 2017 <copyright holder> <email>
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

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "drawable.h"
#include "text.h"
#include "image.h"

class TextBox : public Drawable
{
public:
    TextBox();
    ~TextBox();
    virtual void Draw();
    virtual void Update();
    virtual void OnTimedTick();
    virtual void OnMouseDown(SDL_Event* event);
    virtual void OnMouseUp(SDL_Event* event);
    virtual void OnMouseMotion(SDL_Event* event);
    virtual void OnInputCaptured(SDL_Event* event);

    bool        cursorVisible = false;
    Text*       textleft;
    Text*       textright;
    GPU_Image*  background;
    GPU_Rect    bgsrcrect;
    GPU_Image*  cursorimage;
    GPU_Rect    cursorsrcrect;
    GPU_Rect    cursordestrect;
    
    std::string text;
    std::string composition;
    Sint32 cursor;
    Sint32 selection_len;
    
    
};

#endif // TEXTBOX_H
