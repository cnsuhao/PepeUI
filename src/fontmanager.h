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

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "includes.h"
#include "drawable.h"
#include "globals.h"

class FontManager
{
public:
    FontManager();
    ~FontManager();
    
    static TTF_Font* GetFont(Font font, int fontsize);

private:
    
    
    static std::map<Font, std::string> fontnames;
    
    static std::map<Font, std::map<int, TTF_Font*>> fontcollection;
    
    // Map of drawables to be drawn
    //static std::map<const char*, Drawable*> Drawables;
    
    
};

#endif // FONTMANAGER_H
