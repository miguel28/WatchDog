/*
 *  MK_Backgrounds.h
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <SDL/SDL_TTF.h>

#include "MK_Graphics.h"

class MK_Background{
public:
	int SizeX,SizeY;
	int x,y;
	Uint8 ScrollTimeX,ScrollTimeY;
	Uint16 Time;
	Sint16 Counter;
	Sint8 Factor;
	Uint8 Aumenta;
	Uint8 Alpha,tAlpha;
	Uint8 GfxCreated;
	
	SDL_Surface *Graphic;
	SDL_Surface *GfxEffect;
	MK_Background(char *Filename,Uint32 KeyColor, Uint8 Key, int FSizeX, int FSizeY);
	void DrawBackground(SDL_Surface *Screen);
	void DrawBackgroundInt(SDL_Surface *gfx,SDL_Surface *Screen);
	void DrawBackgroundParallax(SDL_Surface *Screen, Sint16 ParallaxX,Sint16 ParallaxY, Uint16 timex, Uint16 timey);
	void SineEffect(SDL_Surface *Screen,Uint8 Longitude,double Interval,Uint8 time);
	void ExpoEffect(SDL_Surface *Screen,Uint8 Longitude, Sint8 Low, Sint8 High, Uint8 Interval1, Uint8 Interval2);
	void MoveLine(SDL_Surface *Screen,int Magnitude, int yy);
	void CreateGfxEffect(Uint32 width, Uint32 height);
	void DeleteGfxEffect();
};
