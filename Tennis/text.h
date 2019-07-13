#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
using namespace std;
 
class Text{

public:

    Text(const std::string &text, const SDL_Color &color, TTF_Font *font)
    :
       surface(0),
       color(color),
       font(font)
 
	{
     
        surface = generate(text);
    }

    void render(int x, int y, SDL_Surface *destination){

        SDL_Rect rect = {x,y};
        SDL_BlitSurface(surface, 0, destination, &rect);
    }

    void updateText(const std::string &text){

        SDL_Surface *temp = generate(text);
        std::swap(temp, surface);
        SDL_FreeSurface(temp);
    }

private:

    SDL_Surface *generate(const std::string &text){

        SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
        
        return surface;
    }

    SDL_Surface *surface;
    SDL_Color color;
    TTF_Font *font;
    //disable copying
    Text(const Text &);
    Text &operator = (const Text &);
};