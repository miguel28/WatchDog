/*
 *  MK_Graphics.h
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;


#define TRANSPARENT	0xFF00FF
#define PI 3.14159265

Uint32 MK_getpixel(SDL_Surface *surface, int x, int y);
void MK_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 *MK_PixelsArray(SDL_Surface *surface);
SDL_Surface *MK_ArrayToSurface(Uint32 *array, int w, int h);
void MK_SetGrayScaleColor(SDL_Surface *src,Uint32 Key, Uint8 Type);
Uint32 MK_GreyPixel(Uint32 pix);
Uint32 MK_BlackPixel(Uint32 pix);
void MK_HFlipSurface(SDL_Surface *surface);
void MK_VFlipSurface(SDL_Surface *surface);

SDL_Surface *MK_SurfaceZoom(SDL_Surface *source, float zoomx, float zoomy);
SDL_Surface *MK_SurfaceRot(SDL_Surface *source, Uint16 Angle, int cx, int cy, Uint8 Resize, Uint32 Key);
