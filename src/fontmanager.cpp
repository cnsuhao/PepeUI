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

#include "fontmanager.h"

// Static member definitions
std::map<Font, std::string> FontManager::fontnames = {
        {Font::Main,            "cmunrm.ttf"},
        {Font::ConsoleFont,     "cmunrm.ttf"}
    };
std::map<Font, std::map<int, TTF_Font*>> FontManager::fontcollection;
//std::map<const char*, Drawable*> FontManager::Drawables = std::map<const char*, Drawable*>();



FontManager::FontManager()
{

    
}

FontManager::~FontManager()
{
    // Free fonts
    for (auto fontlist : fontcollection) {
        for (auto font : fontlist.second) {
            TTF_CloseFont(font.second);
            font.second = NULL;
        }
    }
    
    
    // Delete drawables
    /*for (auto drawable : Drawables) {
        delete drawable.second;
    }*/
}


// TODO: remove else and move return out of if
TTF_Font * FontManager::GetFont(Font font, int fontsize) {
    // Check if font is loaded already
    if (fontcollection[font][fontsize] == nullptr) {
        // Load requested font
        fontcollection[font][fontsize] = TTF_OpenFont(("Content/Fonts/" + fontnames[font]).c_str(), fontsize);
        
        // Error checking
        if (!fontcollection[font][fontsize]) printf("Main Font failed to load!\n");
        
        // Return font
        return fontcollection[font][fontsize];
        
    } else {
        // Return font
        return fontcollection[font][fontsize];
    }
}

