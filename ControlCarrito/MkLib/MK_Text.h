#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

class MK_Text
{
    public:
    Uint32 x,y;
    Uint8 Alpha,tAlpha;
    SDL_Surface *Graphic;
    TTF_Font *Font;
    SDL_Color Color;
    bool Created;
          
    MK_Text(char* Filename, Uint8 SizeFont, Uint8 R, Uint8 G, Uint8 B);
    void SetText(char* Text);
    void SetColor(Uint8 R, Uint8 G, Uint8 B);
    void DrawText(SDL_Surface *Screen);
    void FreeGraphic();
};
