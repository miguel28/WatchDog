/*
 *  MikeLibrary.h
 *  SDLExample
 *
 *  Created by mike on 3/2/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "SDL_rotozoom.h"

using namespace std;


typedef struct{
	Uint8 A,Z,X,S,Q,W,E,D,C,Shift,Enter,Up,Down,Left,Right; 
}KeysType;

typedef struct{
	KeysType Newpress,Held;
}PadType;

typedef struct{
	Uint8 RClick, LClick;
}ClickType;

typedef struct{
	Uint16 x,y;
	ClickType Newpress,Held;
}MouseType;


void ClearKeyboard();
void CheckKeyboardMouse();
void ReadMouse(int *x, int *y);


#include "MK_Sprites.h"
#include "MK_Backgrounds.h"
#include "MK_Graphics.h"
#include "MK_Video.h"
#include "MK_Math.h"
#include "MK_Text.h"
