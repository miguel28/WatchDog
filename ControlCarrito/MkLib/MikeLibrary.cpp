/*
 *  MikeLibrary.c
 *  SDLExample
 *
 *  Created by mike on 3/2/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MikeLibrary.h"

SDL_Event _event;
extern PadType Pad;
extern MouseType Mouse;

void ClearKeyboard()
{
	Pad.Newpress.A=0;
	Pad.Newpress.Z=0;
	Pad.Newpress.X=0;
	Pad.Newpress.S=0;
	Pad.Newpress.Q=0;
	Pad.Newpress.W=0;
	Pad.Newpress.E=0;
	Pad.Newpress.D=0;
	Pad.Newpress.C=0;
	Pad.Newpress.Shift=0;
	Pad.Newpress.Enter=0;
	Pad.Newpress.Up=0;
	Pad.Newpress.Down=0;
	Pad.Newpress.Left=0;
	Pad.Newpress.Right=0;
	
	Mouse.Newpress.RClick=0;
	Mouse.Newpress.LClick=0;
}

void CheckKeyboardMouse()
{
	ClearKeyboard();
	if(SDL_PollEvent(&_event)){
		switch (_event.type) 
		{
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch(_event.key.keysym.sym){
					case SDLK_ESCAPE:
						SDL_Quit();
						exit(0);
						break;
					
					case SDLK_LEFT:
						Pad.Newpress.Left=1;
						Pad.Held.Left=1;
						break;
					case SDLK_RIGHT:
						Pad.Newpress.Right=1;
						Pad.Held.Right=1;
						break;
					case SDLK_UP:
						Pad.Newpress.Up=1;
						Pad.Held.Up=1;
						break;
					case SDLK_DOWN:
						Pad.Newpress.Down=1;
						Pad.Held.Down=1;
						break;		
					case SDLK_RETURN:
						Pad.Newpress.Enter=1;
						Pad.Held.Enter=1;
						break;	
					case SDLK_LSHIFT:
						Pad.Newpress.Shift=1;
						Pad.Held.Shift=1;
						break;
					case SDLK_q:
						Pad.Newpress.Q=1;
						Pad.Held.Q=1;
						break;
					case SDLK_a:
						Pad.Newpress.A=1;
						Pad.Held.A=1;
						break;
					case SDLK_z:
						Pad.Newpress.Z=1;
						Pad.Held.Z=1;
						break;
					case SDLK_w:
						Pad.Newpress.W=1;
						Pad.Held.W=1;
						break;
					case SDLK_s:
						Pad.Newpress.S=1;
						Pad.Held.S=1;
						break;
					case SDLK_x:
						Pad.Newpress.X=1;
						Pad.Held.X=1;
						break;
					case SDLK_e:
						Pad.Newpress.E=1;
						Pad.Held.E=1;
						break;
					case SDLK_d:
						Pad.Newpress.D=1;
						Pad.Held.D=1;
						break;
					case SDLK_c:
						Pad.Newpress.C=1;
						Pad.Held.C=1;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(_event.key.keysym.sym){
					case SDLK_LEFT:
						Pad.Held.Left=0;
						break;
					case SDLK_RIGHT:
						Pad.Held.Right=0;
						break;
					case SDLK_UP:
						Pad.Held.Up=0;
						break;
					case SDLK_DOWN:
						Pad.Held.Down=0;
						break;		
					case SDLK_RETURN:
						Pad.Held.Enter=0;
						break;	
					case SDLK_LSHIFT:
						Pad.Held.Shift=0;
						break;
					case SDLK_q:
						Pad.Held.Q=0;
						break;
					case SDLK_a:
						Pad.Held.A=0;
						break;
					case SDLK_z:
						Pad.Held.Z=0;
						break;
					case SDLK_w:
						Pad.Held.W=0;
						break;
					case SDLK_s:
						Pad.Held.S=0;
						break;
					case SDLK_x:
						Pad.Held.X=0;
						break;
					case SDLK_e:
						Pad.Held.E=0;
						break;
					case SDLK_d:
						Pad.Held.D=0;
						break;
					case SDLK_c:
						Pad.Held.C=0;
						break;
						
					default:
						break;
				}
				break;
			case SDL_MOUSEMOTION:
                Mouse.x=_event.motion.x; 
				Mouse.y=_event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
					switch (_event.button.button) {
						case SDL_BUTTON_RIGHT:
							Mouse.Newpress.RClick=1;
							Mouse.Held.RClick=1;
							break;
						case SDL_BUTTON_LEFT:
							Mouse.Newpress.LClick=1;
							Mouse.Held.LClick=1;
							break;
						default:
							break;
					}
					//printf("Mouse button %d pressed at (%d,%d)\n",
					//event.button.button, event.button.x, event.button.y);
					break;
				break;
			case SDL_MOUSEBUTTONUP:
				switch (_event.button.button) {
					case SDL_BUTTON_RIGHT:
						Mouse.Held.RClick=0;
						break;
					case SDL_BUTTON_LEFT:
						Mouse.Held.LClick=0;
						break;
					default:
						break;
				}
				//printf("Mouse button %d pressed at (%d,%d)\n",
				//event.button.button, event.button.x, event.button.y);
				break;
		}
		
	}
	
}

void ReadMouse(int *x, int *y)
{
	
    while ( SDL_PollEvent(&_event) ) {
        switch (_event.type) {
            case SDL_MOUSEMOTION:
                //printf("Mouse moved by %d,%d to (%d,%d)\n",event.motion.xrel, event.motion.yrel,event.motion.x, event.motion.y);
                *x=_event.motion.x; 
				*y=_event.motion.y;
                
				break;
            case SDL_MOUSEBUTTONDOWN:
                //printf("Mouse button %d pressed at (%d,%d)\n",
                       //event.button.button, event.button.x, event.button.y);
                break;
        }
    }
}






