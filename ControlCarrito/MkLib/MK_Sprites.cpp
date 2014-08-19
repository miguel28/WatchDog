/*
 *  MK_Sprites.cpp
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */
#include "MK_Sprites.h"


MK_Sprite::MK_Sprite(char *Filename, Uint32 KeyColor, Uint8 Key, Uint16 FSizeX,Uint16 FSizeY,Uint16 SizeX,Uint16 SizeY)
{
	
	if(Key){
		Graphic = SDL_LoadBMP(Filename);
		SDL_SetColorKey(Graphic, SDL_SRCCOLORKEY, KeyColor);
	}
	else Graphic = IMG_Load(Filename);
	
	FrameSizeX=FSizeX;
	FrameSizeY=FSizeY;
	SheetSizeX=SizeX;
	SheetSizeY=SizeY;
	FrameTime=0;	
	FrameAnim=0;
	tAlpha=Alpha=255;
	x=0;	
	y=0;	
	if(FrameSizeX==0)FrameSizeX=1;
	if(FrameSizeY==0)FrameSizeY=1;
	if(SheetSizeX==0)SheetSizeX=1;
	if(SheetSizeY==0)SheetSizeY=1;
	
}

void MK_Sprite::DrawSprite(SDL_Surface *Screen, int frame)
{
	int framey = frame/SheetSizeX;
	int framex = frame-(SheetSizeX*framey);
	SDL_Rect Sframe={framex*FrameSizeX,framey*FrameSizeY,FrameSizeX,FrameSizeY};
	SDL_Rect dest={x,y,FrameSizeX,FrameSizeY};
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(Graphic, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
	SDL_BlitSurface(Graphic,&Sframe,Screen,&dest);
}

void MK_Sprite::DrawSpriteAnim(SDL_Surface *Screen, Uint8 framestart, Uint8 framefinish, Uint8 Speed)
{
	Uint8 tempFrame;
	if(FrameAnim<=framefinish&&FrameAnim>=framestart){
		FrameTime++;
		if(FrameTime>=Speed){
			FrameAnim++;
			FrameTime=0;
		}
		if(FrameAnim>framefinish)FrameAnim = framestart;
	}
	else {
		FrameAnim=framestart;
	}
	tempFrame=FrameAnim;
	DrawSprite(Screen, tempFrame);
}

void MK_Sprite::HFlip()
{
	int a,b,i,j; 
	SDL_Surface *TempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, FrameSizeX, FrameSizeY, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
	SDL_Rect TempRect;
	// a -> Frame X
	// b -> Frame Y
	for(b=0; b<SheetSizeY; b++)
	{
		for(a=0; a<SheetSizeX;a++)
		{
			TempRect.x = a*FrameSizeX;
			TempRect.y = b*FrameSizeY;
			TempRect.w = FrameSizeX;
			TempRect.h = FrameSizeY;
			
			for(j=0;j<FrameSizeY;j++)
			{
				for(i=0; i<FrameSizeX;i++)
				{
					MK_putpixel(TempSurface, i, j, 0x00FF00FF);
				}
			}
						
			SDL_BlitSurface(Graphic,&TempRect,TempSurface,NULL);
			
			MK_HFlipSurface(TempSurface);
			
			/*for(j=0;j<FrameSizeY;j++)
			{
				for(i=0; i<FrameSizeX;i++)
				{
					MK_putpixel(Graphic, (a*FrameSizeX)+i, (b*FrameSizeY)+j, 0x00FF00FF);
				}
			}*/
			
			SDL_BlitSurface(TempSurface,NULL,Graphic,&TempRect);
			
			
			
			
		}
	}
}
void MK_Sprite::VFlip()
{
	int a,b,i,j; 
	SDL_Surface *TempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, FrameSizeX, FrameSizeY, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
	SDL_Rect TempRect;
	// a -> Frame X
	// b -> Frame Y
	for(b=0; b<SheetSizeY; b++)
	{
		for(a=0; a<SheetSizeX;a++)
		{
			TempRect.x = a*FrameSizeX;
			TempRect.y = b*FrameSizeY;
			TempRect.w = FrameSizeX;
			TempRect.h = FrameSizeY;
			
			for(j=0;j<FrameSizeY;j++)
			{
				for(i=0; i<FrameSizeX;i++)
				{
					MK_putpixel(TempSurface, i, j, 0x00FF00FF);
				}
			}
			
			SDL_BlitSurface(Graphic,&TempRect,TempSurface,NULL);
			
			MK_VFlipSurface(TempSurface);
			
			/*for(j=0;j<FrameSizeY;j++)
			 {
			 for(i=0; i<FrameSizeX;i++)
			 {
			 MK_putpixel(Graphic, (a*FrameSizeX)+i, (b*FrameSizeY)+j, 0x00FF00FF);
			 }
			 }*/
			
			SDL_BlitSurface(TempSurface,NULL,Graphic,&TempRect);
			
			
			
			
		}
	}
}

void MK_Sprite::CreateGfxEffect(Uint32 width, Uint32 height)
{
	GfxEffect=SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
	SDL_BlitSurface(Graphic,NULL,GfxEffect,NULL);	
}

void MK_Sprite::DeleteGfxEffect()
{
	SDL_FreeSurface(GfxEffect);
}

void MK_Sprite::Rot(Uint16 Angle, int cx, int cy, Uint8 Resize, Uint32 Key)
{
	if(!GfxEffect)return;
	GfxEffect = MK_SurfaceRot(Graphic,Angle,cx,cy,Resize,Key);
}

void MK_Sprite::DrawEffect(SDL_Surface *Screen)
{
	if(!GfxEffect)return;
	

	SDL_Rect Sframe={0,0,FrameSizeX*1.5,FrameSizeY*1.5};
	SDL_Rect dest={x,y,FrameSizeX,FrameSizeY};
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(GfxEffect, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
	SDL_BlitSurface(GfxEffect,&Sframe,Screen,&dest);
	//SDL_FreeSurface(GfxEffect);
}
