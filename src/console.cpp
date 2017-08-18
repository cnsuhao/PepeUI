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

#define MessageTime 5000

#include "console.h"


// Console line struct
struct ConsoleLine {
  Text*             text;
  ConsoleLineType   type;
  uint32            timeadded;
};

// List of console lines
static std::vector<ConsoleLine*> ConsoleContent;

// Pointer to application info for easy object creation
//static ApplicationContext* appinfo;

// Should layout update
static bool shouldUpdate = true;

Console::Console()
{
    // Store pointers
    //appinfo = AppContext;
    //this->globals = globals;
    this->target  = globals->window;
    
    // Add event handles
    handles.UsingTimer   = true;
    handles.TimerTime    = 500;
    handles.UsingKeyUp   = true;
    
    // Make sure the texture is untouched
    isTextureUsed = false;
    
    // Update
    Update();
}

Console::~Console()
{
    // NOTE: Make sure only one instance of Console is ever created.
    
    // Delete lines
    for (auto line : ConsoleContent) {
        delete line->text;
        delete line;
    }

}

void Console::Draw()
{
    if (shouldUpdate) {
        Update();
        globals->shouldRefresh = true;
    }
    for (auto line : ConsoleContent)
    {
        line->text->Draw();
    }
}

void Console::Update()
{
    int i = 0;
    
    for (auto line : ConsoleContent)
    {
        line->text->Update();
        line->text->Position.x = line->text->texture->w/2.0f + 15;
        line->text->Position.y = line->text->texture->h/2.0f + (i*line->text->texture->h) + 15;
        i++;
    }
    
    shouldUpdate = false;
}

void Console::OnTimedTick()
{
    bool checking = true;
    while (checking){
        if (ConsoleContent.size() > 0) {
            if(SDL_GetTicks() - ConsoleContent[0]->timeadded > MessageTime) {
                ConsoleLine* line = ConsoleContent[0];
                delete ConsoleContent[0]->text;
                ConsoleContent[0]->text = NULL;
                ConsoleContent.erase(ConsoleContent.begin());
                delete line;
            } else {
                checking = false;
            }
        } else {
            checking = false;
        }
    }
    
    Update();
}

void Console::OnKeyUp(SDL_Event* event)
{
    if(event->key.keysym.sym==SDLK_e)
        Console::Log("This is supposed to be and error", ConsoleLineType::Error);
    if(event->key.keysym.sym==SDLK_i)
        Console::Log("This is supposed to be and information", ConsoleLineType::Log);
    if(event->key.keysym.sym==SDLK_w)
        Console::Log("This is supposed to be and warning", ConsoleLineType::Warning);
    if(event->key.keysym.sym==SDLK_l)
        Console::Log("Content/Textures/Somefile.png", ConsoleLineType::LoadError);
}

void Console::Log(std::string Message, ConsoleLineType Type)
{
    // Create a new line
    ConsoleLine* line = new ConsoleLine();
    
    
    // Fill line with data
    line->text       = new Text(Message, FontManager::GetFont(Font::Main, 32));
    line->type       = Type;
    line->timeadded  = SDL_GetTicks();
    
    // Color coding
    if (Type == ConsoleLineType::Error) {
        line->text->Color = {255,15,15,255};
    } else if (Type == ConsoleLineType::LoadError){
        line->text->Color = {255,15,15,255};
        line->text->text = "Failed to load: " + Message;
   } else if (Type == ConsoleLineType::Warning) {
        line->text->Color = {255,220,15,255};
    }
    
    
    
    // Insert the new line
    ConsoleContent.push_back(line);
    
    // Update layout
    shouldUpdate = true;
    
    
    // TODO: Uncomment later, when console succesfully implemented.
    // Remove the first item if more than 5 messages in console
    //if (ConsoleContent.size() > 5)
    //    ConsoleContent.erase(ConsoleContent.begin());
}

