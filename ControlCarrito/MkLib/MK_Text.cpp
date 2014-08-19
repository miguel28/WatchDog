#include "MK_Text.h"
MK_Text::MK_Text(char* Filename, Uint8 SizeFont, Uint8 R, Uint8 G, Uint8 B)
{
    Font = TTF_OpenFont(Filename,SizeFont);
	Color.r = R;
	Color.b = B;
    Color.g = G;
    if(Font)Created=true;
    x = 0;
    y = 0; 
	Alpha=255;
}
void MK_Text::SetText(char* Text)
{
    //SDL_FreeSurface(Graphic);
    Graphic = TTF_RenderText_Solid(Font,Text,Color);
}
void MK_Text::SetColor(Uint8 R, Uint8 G, Uint8 B)
{
    Color.r = R;
	Color.b = B;
    Color.g = G;
}
void MK_Text::DrawText(SDL_Surface *Screen)
{
	SDL_Rect dest={x,y,Graphic->w,Graphic->h};
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(Graphic, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
	SDL_BlitSurface(Graphic,NULL,Screen,&dest);
}
void MK_Text::FreeGraphic()
{
    SDL_FreeSurface(Graphic);
}
