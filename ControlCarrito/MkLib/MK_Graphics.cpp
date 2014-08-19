/*
 *  MK_Graphics.cpp
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Graphics.h"

Uint32 MK_getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
	/*if((x<0)||(x>surface->w-1)||(y<0)||(y>surface->h-1))
	{
		cout << "MK_getpixel: Segmentation Error" << endl;
		return 0;
	}*/
    switch(bpp) {
		case 1:
			return *p;
			break;
			
		case 2:
			return *(Uint16 *)p;
			break;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;
			
		case 4:
			return *(Uint32 *)p;
			break;
			
		default:
			return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void MK_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
	/*if((x<0)||(x>surface->w-1)||(y<0)||(y>surface->h-1))
	{
		cout << "MK_putpixel: Segmentation Error" << endl;
	}
	else*/
    switch(bpp) {
		case 1:
			*p = pixel;
			break;
			
		case 2:
			*(Uint16 *)p = pixel;
			break;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
			
		case 4:
			*(Uint32 *)p = pixel;
			break;
    }
}

Uint32 *MK_PixelsArray(SDL_Surface *surface)
{ 
	Uint32 *TempArray=new Uint32[surface->w*surface->h*4]; 
	int i,j;
	for(j=0;j<surface->h;j++)
	{
		for(i=0; i<surface->w;i++)
		{
			TempArray[(j*surface->w)+i]=MK_getpixel(surface, i, j);
		}
		
	}
	return TempArray;
	
}

SDL_Surface *MK_ArrayToSurface(Uint32 *array, int w, int h)
{
	int i,j;
	SDL_Surface *surface= SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	
	for(j=0;j<h;j++)
	{
		for(i=0; i<w;i++)
		{
			MK_putpixel(surface, i, j, array[(w*j)+i]);
		}
	}
	return surface;
	
}

void MK_SetGrayScaleColor(SDL_Surface *src,Uint32 Key, Uint8 Type)
{
	//SDL_Surface *dest=SDL_CreateRGBSurface(SDL_SWSURFACE, src->w, src->h, 32, 0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff);
	Uint32 *pixels=MK_PixelsArray(src);
	
	int i,j;
	for(i=0; i<src->w; i++)
	{
		for(j=0; j<src->h; j++)
		{
			Uint32 pix = pixels[(j*src->w)+i];
			if(pix!=Key)
			{
				if(Type==1)MK_putpixel(src, i, j, MK_GreyPixel(pix));
				if(Type==2)MK_putpixel(src, i, j, MK_BlackPixel(pix));
			}
			else 
			{
				MK_putpixel(src, i, j, Key);
			}
			
		}
	}
	delete[] pixels;
}

Uint32 MK_GreyPixel(Uint32 pix)
{
	Uint32 R,G,B,lower;
	
	
	R=pix>>16;
	
	G=pix<<16;
	G=G>>24;
	
	B=pix<<24;
	B=B>>24;
	
	lower=(R+G+B)/3;
	
	return (lower<<16)|(lower<<8)|lower;
	
}
Uint32 MK_BlackPixel(Uint32 pix)
{
	Uint32 R,G,B,lower;
	
	
	R=pix>>16;
	
	G=pix<<16;
	G=G>>24;
	
	B=pix<<24;
	B=B>>24;
	
	//cout << pix<<" "<<R<<" "<<G<<" "<<B<<endl;
	
	if(R<G)lower=R;
	if(R>G)lower=G;
	if(R==G)lower=G;
	
	//if(lower<B)lower=R;
	if(lower>B)lower=B;
	if(lower==B)lower=B;
	
	return (lower<<16)|(lower<<8)|lower;
	
}

void MK_HFlipSurface(SDL_Surface *surface)
{
	Uint32 *pixels=MK_PixelsArray(surface);
	
	int i,j;
	for(j=0;j<surface->h;j++)
	{
		for(i=0; i<surface->w;i++)
		{
			MK_putpixel(surface, i, j, pixels[(surface->w*j)+surface->w-i]);
		}
	}
	delete[] pixels;
}
void MK_VFlipSurface(SDL_Surface *surface)
{
	Uint32 *pixels=MK_PixelsArray(surface);
	
	int i,j;
	for(j=surface->h-1;j>=0;j--)
	{
		for(i=0; i<surface->w;i++)
		{
			MK_putpixel(surface, i, surface->h-j, pixels[(surface->w*j)+i]);
		}
	}
	delete[] pixels;
}

/////////////////////////////// Linear Tranformations////////////////////////////
SDL_Surface *MK_SurfaceZoom(SDL_Surface *source, float zoomx, float zoomy)
{
	SDL_Surface *TempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, (source->w)*zoomx, (source->h-1)*zoomy, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
	int i,j;
	
	for(j=0; j<(source->h-1)*zoomy-1; j++)
	{
		for(i=0; i<(source->w)*zoomx; i++)
		{
			/*if((source->h)<(j/zoomy))fix=(source->h)-(j/zoomy);
			else fix=0;*/
			
			Uint32 Pix;
			Pix= MK_getpixel(source,(i/zoomx),(j/zoomy));
			MK_putpixel(TempSurface, i, j, Pix);
			
		}
	}
	
	return TempSurface;
}

SDL_Surface *MK_SurfaceRot(SDL_Surface *source, Uint16 Angle, int cx, int cy, Uint8 Resize, Uint32 Key)
{
	//SDL_Surface *TempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, (source->w)*3, (source->h-1)*3, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
	//SDL_Surface *TempSurface2 = SDL_CreateRGBSurface(SDL_HWSURFACE, (source->w)*3, (source->h-1)*3, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
	int NewSizeRotableX,NewSizeRotableY;
	Uint8 Fix; 
	if(Resize){
		if((source->w)>=(source->h))
		{
			NewSizeRotableX=(int)sqrt(2*((source->w)*(source->w)));
			Fix=(NewSizeRotableX-source->w)/2;
			NewSizeRotableY=NewSizeRotableX;
		}
		else
		{
			NewSizeRotableX=(int)sqrt(2*((source->h)*(source->h)));
			Fix=(NewSizeRotableX-source->h)/2;
			NewSizeRotableY=NewSizeRotableX;
		}
	}
	else 
	{
		NewSizeRotableX=(source->w);
		NewSizeRotableY=(source->h);
		Fix=0; 
	}

	SDL_Surface *TempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, NewSizeRotableX, NewSizeRotableY, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
	if(Angle>=360)Angle-=360;
	int i,j;
	int xp, yp;
	Uint32 Pix;
	double Rad=(double)(Angle*(M_PI/180));
	for(j=0; j<NewSizeRotableY; j++)
	{
		for(i=0; i<NewSizeRotableX; i++)
		{
			
			
			xp= (int)(((i-cx-Fix)*cos(Rad))-((j-cy-Fix)*sin(Rad)))+cx;
			yp= (int)(((i-cx-Fix)*sin(Rad))+((j-cy-Fix)*cos(Rad)))+cy;
			
			
			if(xp<0||yp<0||xp>=source->w||yp>=source->h)Pix=Key;
			else Pix=MK_getpixel(source, xp, yp);
	
			MK_putpixel(TempSurface, i, j, Pix);
			
		}
	}
	SDL_SetColorKey(TempSurface, SDL_SRCCOLORKEY, Key);
	return TempSurface;
}

Uint32 MK_GetSizeRotedGfx(Uint32 w, Uint32 h)
{
	
	if(w>=h)
	{
		return (Uint32)(sqrt(2*w*w));
	}
	else
	{
		return (Uint32)(sqrt(2*h*h));

	}
}


