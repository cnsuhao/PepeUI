
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

#include "textbox.h"
#include "mathutils.h"
#include "console.h"

TextBox::TextBox() {
    // Store pointers
    this->target  = globals->window;
    
    // Add event handles
    handles.UsingTimer   = true;
    handles.TimerTime    = 500;
    handles.UsingKeyUp   = true;
    handles.UsingMouseUp = true;
    
    // Make sure the texture is untouched
    isTextureUsed = false;
    
    // Init text obj
    textleft = new Text("Left");
    textright = new Text("Right");
    
    // Set position
    Position = vec2(300,400);
    
    // Create a background
    background = GPU_CreateImage(10,10,GPU_FormatEnum::GPU_FORMAT_RGB);
    bgsrcrect = {0,0,10,10};
    
    // Create cursor
    SDL_Surface* cursorsurface = SDL_CreateRGBSurface(0,5,5,32,0,0,0,0);
    SDL_FillRect(cursorsurface, NULL, SDL_MapRGB(cursorsurface->format, 255, 0, 0));
    cursorimage = GPU_CopyImageFromSurface(cursorsurface);
    SDL_FreeSurface(cursorsurface);
    cursorsrcrect = {0,0,5,5};
    
    // Update
    Update();
}

TextBox::~TextBox() {
    delete textleft;
    delete textright;
    GPU_FreeImage(background);
    GPU_FreeImage(cursorimage);
}


void TextBox::Draw()
{
    GPU_BlitRect(background, &bgsrcrect, target, &rect);
    textleft->Draw();
    textright->Draw();
    if (cursorVisible)
        GPU_BlitRect(cursorimage, &cursorsrcrect, target, &cursordestrect);
}

void TextBox::Update()
{
    // Update texts
    textleft->Update();
    textright->Update();
    
    // Set positions
    textleft->Position.x = Position.x;
    textleft->Position.y = Position.y;
    textright->Position.x = Position.x+(textleft->srcrect.w/2.0f)+(textright->srcrect.w/2.0f);
    textright->Position.y = Position.y;
    
    
    // Update rect
    rect.x = Position.x - (textleft->srcrect.w/2.0f);
    rect.y = Position.y - (textleft->srcrect.h/2.0f);
    rect.w = (textleft->srcrect.w)+(textright->srcrect.w);
    rect.h = (textleft->srcrect.h);
    
    // Update cursor rect
    cursordestrect = {
        rect.x+textleft->srcrect.w,
        rect.y-4,
        3, textleft->srcrect.h
    };
    
}

void TextBox::OnTimedTick()
{
    Update();
    text = textleft->text + textright->text;
    if (globals->CaptureStack.size() > 0) {
        if(globals->CaptureStack.back().drawableID == id)
            cursorVisible = !cursorVisible;
    }else{
        cursorVisible = false;
    }
}

void TextBox::OnMouseDown(SDL_Event* event)
{

}

void TextBox::OnMouseUp(SDL_Event* event)
{
    
    if (globals->CaptureStack.size() == 0) {
        if (MathUtils::PointRectIntersects(vec2(event->button.x, event->button.y),rect)) {
            Console::Log("Clicked textbox!", ConsoleLineType::Log);
            globals->CaptureStack.push_back({id, true, false});
            Update();
        }
    }
}

void TextBox::OnMouseMotion(SDL_Event* event)
{

}

void TextBox::OnInputCaptured(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_BACKSPACE && textleft->text.size() > 0)
                textleft->text.pop_back();
            if(event->key.keysym.sym == SDLK_LEFT && textleft->text.size() > 0) {
                textright->text.insert(textright->text.begin(), textleft->text.back());
                textleft->text.pop_back();
            }
            if(event->key.keysym.sym == SDLK_RIGHT && textright->text.size() > 0) {
                textleft->text.push_back(textright->text[0]);
                textright->text.erase(textright->text.begin());
            }
            if(event->key.keysym.sym == SDLK_END && textright->text.size() > 0) {
                textleft->text += textright->text;
                textright->text.clear();
            }
            if(event->key.keysym.sym == SDLK_HOME && textleft->text.size() > 0) {
                textright->text.insert(0, textleft->text);
                textleft->text.clear();
            }
            Update();
            break;
        case SDL_TEXTINPUT:
            /* Add new text onto the end of our text */
            textleft->text += event->text.text;
            Update();
            break;
    }
}
