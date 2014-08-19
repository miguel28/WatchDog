/*
 *  MK_Backgrounds.cpp
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Backgrounds.h"

MK_Background::MK_Background(char *Filename, Uint32 KeyColor, Uint8 Key, int FSizeX, int FSizeY)
{	
	if(Key)
	{
		Graphic = SDL_LoadBMP(Filename);
		SDL_SetColorKey(Graphic, SDL_SRCCOLORKEY, KeyColor);
	}
	else
	{
		Graphic = IMG_Load(Filename);
	}
	
	SizeX=FSizeX;
	SizeY=FSizeY;
	x=0;
	y=0;
	Time=0;
	Counter=0;
	GfxCreated=0;
	Alpha=255;
	tAlpha=255;
	ScrollTimeX=0;
	ScrollTimeY=0;
}

void MK_Background::DrawBackground(SDL_Surface *Screen)
{
	SDL_Rect area={x,y,SizeX,SizeY};
	SDL_BlitSurface(Graphic,&area,Screen,NULL);
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(Graphic, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
}
void MK_Background::DrawBackgroundInt(SDL_Surface *gfx,SDL_Surface *Screen)
{
	SDL_Rect area={x,y,SizeX,SizeY};
	SDL_BlitSurface(gfx,&area,Screen,NULL);
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(gfx, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
	
}

void MK_Background::DrawBackgroundParallax(SDL_Surface *Screen, Sint16 ParallaxX,Sint16 ParallaxY, Uint16 timex, Uint16 timey)
{
	ScrollTimeX++;
	if(ScrollTimeX>=timex)
	{
		x-=ParallaxX;
		ScrollTimeX=0;
	}
	
	ScrollTimeY++;
	if(ScrollTimeY>=timey)
	{
		y-=ParallaxY;
		ScrollTimeY=0;
	}
	
	if(x<=-Graphic->w)x=0;
	if(x>=Graphic->w)x=0;
	if(y<=-Graphic->h)y=0;
	if(y>=Graphic->h)y=0;
	
	SDL_Rect area;
	area.w=SizeX; 
	area.h=SizeY;
	
	if(ParallaxX>0)
	{
		area.x=Graphic->w+x;
	}
	else if(ParallaxX<0)
	{
		area.x=-Graphic->w+x;
	}
	
	if(ParallaxY>0)
	{
		area.y=Graphic->h+y;
	}
	else if(ParallaxY<0)
	{
		area.y=-Graphic->h+y;
	}
	
	SDL_BlitSurface(Graphic,&area,Screen,NULL);
	DrawBackgroundInt(Graphic,Screen);
}
void MK_Background::SineEffect(SDL_Surface *Screen,Uint8 Longitude, double Interval,Uint8 time)
{
	
	if(GfxCreated){
		int Line;
	
		Time++;
		if(Time==time){
			Time=0;
			Counter++;
			if(Counter==360/Interval)Counter=0;
			
			if(y>=0&&y+SizeY<=Graphic->h-1)
			{
				for(Line=y;Line<y+SizeY;Line++){
					MoveLine(Screen,Longitude*sin(((Line-Counter)*Interval*PI)/180), Line);
				}
			}
			else if((y<0)&&(y>-SizeY))
			{
				for(Line=0;Line<y+SizeY;Line++){
					MoveLine(Screen,Longitude*sin(((Line-Counter)*Interval*PI)/180), Line);
				}
			}
			else if((y+SizeY>=Graphic->h-1) && (y < Graphic->h-1))
			{
				for(Line=y;Line<Graphic->h-1;Line++){
					MoveLine(Screen,Longitude*sin(((Line-Counter)*Interval*PI)/180), Line);
				}
				
			}
			/*
			for(Line=0;Line<(Graphic->h-1);Line++){
				MoveLine(Screen,Longitude*sin(((Line-Counter)*Interval*PI)/180), Line);
			}*/
		}
		DrawBackgroundInt(GfxEffect,Screen);
	}
	
}

void MK_Background::ExpoEffect(SDL_Surface *Screen,Uint8 Longitude, Sint8 Low, Sint8 High, Uint8 Interval1, Uint8 Interval2)
{
	
	if(GfxCreated){
		int Line;
	
		if(Aumenta)Counter+=Interval2;
		else Counter-=Interval1;
	
		if(Aumenta&&Counter>High)Aumenta=0;
		if(!Aumenta&&Counter<Low)Aumenta=1;
	
		if(y>=0&&y+SizeY<=Graphic->h-1)
		{
			for(Line=y;Line<y+SizeY;Line++){
				MoveLine(Screen,((Line-(Graphic->h-1))*(Line-(Graphic->h-1)))/((100+Counter)*Longitude), Line);
			}
		}
		else if((y<0)&&(y>-SizeY))
		{
			for(Line=0;Line<y+SizeY;Line++){
				MoveLine(Screen,((Line-(Graphic->h-1))*(Line-(Graphic->h-1)))/((100+Counter)*Longitude), Line);
			}
		}
		else if((y+SizeY>=Graphic->h-1) && (y < Graphic->h-1))
		{
			for(Line=y;Line<Graphic->h-1;Line++){
				MoveLine(Screen,((Line-(Graphic->h-1))*(Line-(Graphic->h-1)))/((100+Counter)*Longitude), Line);
			}
		}
		
		/*for(Line=0;Line<(Graphic->h);Line++){
			MoveLine(Screen,(Line*Line)/((100+Counter)*Longitude), (Graphic->h-1)-Line);
		}*/

		DrawBackgroundInt(GfxEffect,Screen);
	}
}

void MK_Background::MoveLine(SDL_Surface *Screen,int Magnitude, int yy)
{
	int i,j;
	if(Magnitude>0)
		for(j=0; j<Magnitude; j++)MK_putpixel(GfxEffect, j, yy,MK_getpixel(Graphic, Graphic->w-Magnitude+j, yy));
	else 
		for(j=Graphic->w-Magnitude; j<Graphic->w; j++)MK_putpixel(GfxEffect, j, yy, MK_getpixel(Graphic, Graphic->w-Magnitude, yy));
	
	if(x>=0)
	{
		for(i=x; i<x+SizeX ; i++)
		{
			MK_putpixel(GfxEffect, i+Magnitude, yy, MK_getpixel(Graphic, i, yy));
		}
	}
	else
	{
		for(i=0; i<SizeX ; i++)
		{
			MK_putpixel(GfxEffect, i+Magnitude, yy, MK_getpixel(Graphic, i, yy));
		}
	}
}

void MK_Background::CreateGfxEffect(Uint32 width, Uint32 height)
{
	GfxEffect=SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
	SDL_BlitSurface(Graphic,NULL,GfxEffect,NULL);
	GfxCreated=1;
}

void MK_Background::DeleteGfxEffect()
{
	SDL_FreeSurface(GfxEffect);
	GfxCreated=0;
}
