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

#include "drawablemanager.h"

// Static member definitions
std::map<const char*, Drawable*> DrawableManager::drawables = std::map<const char*, Drawable*>();


DrawableManager::DrawableManager()
{
    
}

DrawableManager::~DrawableManager() {
    // Delete drawables
     for (auto drawable : drawables) {
         delete drawable.second;
     }
}

void DrawableManager::AddDrawable(const char* id, Drawable* drawable) {
    if(drawables[id] == nullptr) {
        drawables[id] = drawable;
    } else {
        delete drawables[id];
        drawables[id] = drawable;
    }
}

Drawable * DrawableManager::GetDrawable(const char* id) {
    return drawables[id];
}

std::map<const char *, Drawable *> * DrawableManager::GetDrawableMap() {
    return &drawables;
}


