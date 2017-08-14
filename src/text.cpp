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

#include "text.h"

void Text::load(std::string text, TTF_Font* font, GPU_Target* tar) {
    this->text      = text;
    this->font      = font;
    this->target    = globals->window;
    textsurface     = TTF_RenderUTF8_Blended(font, text.c_str(), Color);
    texture         = GPU_CopyImageFromSurface(textsurface);
    //Update();
}

Text::Text()
{
    load("", FontManager::GetFont(Font::Main, 32), globals->window);
}

Text::Text(std::string text) {
    load(text, FontManager::GetFont(Font::Main, 32),globals->window);
}

Text::Text(std::string text, GPU_Target* target) {
    load(text, FontManager::GetFont(Font::Main, 32), target);
}


Text::Text(std::string text, TTF_Font* font){
    load(text, font, globals->window);
}


Text::~Text()
{

}

void Text::Draw() {
    if (text.size() != 0)
        GPU_Blit(texture, &srcrect, target, Position.x, Position.y);
}

void Text::Update() {
    if (text.size() > 0) {
        SDL_FreeSurface(textsurface);
        textsurface = TTF_RenderUTF8_Blended(font, text.c_str(), Color);
        //srcrect = {0,0,textsurface->w, textsurface->h};
        //GPU_UpdateImage(texture, &srcrect, textsurface, &srcrect);
        GPU_FreeImage(texture);
        texture = GPU_CopyImageFromSurface(textsurface);
        if(text.size() > 0){
            srcrect.w = texture->w;
        }else{
            srcrect.w = 0;
        }
        srcrect.h = texture->h;
    }
}

void Text::SetFont(Font font, int size)
{
    this->font = FontManager::GetFont(font, size);
}



