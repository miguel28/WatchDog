/*
 *  MK_Input.cpp
 *  OpenGLEX
 *
 *  Created by mike on 2/6/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Input.h"
#include <SDL/SDL.h>

using namespace std;

PadType Pad;
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
	Pad.Newpress.Escape=0;
	//Mouse.Newpress.RClick=0;
	//Mouse.Newpress.LClick=0;
}

void ReClearKeyboard()
{
	if(Pad.bNewpress.Q)Pad.Newpress.Q=0;
	if(Pad.bNewpress.A)Pad.Newpress.A=0;
	if(Pad.bNewpress.Z)Pad.Newpress.Z=0;
	if(Pad.bNewpress.W)Pad.Newpress.W=0;
	if(Pad.bNewpress.S)Pad.Newpress.S=0;
	if(Pad.bNewpress.X)Pad.Newpress.X=0;
	if(Pad.bNewpress.E)Pad.Newpress.E=0;
	if(Pad.bNewpress.D)Pad.Newpress.D=0;
	if(Pad.bNewpress.C)Pad.Newpress.C=0;
	if(Pad.bNewpress.Up)Pad.Newpress.Up=0;
	if(Pad.bNewpress.Down)Pad.Newpress.Down=0;
	if(Pad.bNewpress.Left)Pad.Newpress.Left=0;
	if(Pad.bNewpress.Right)Pad.Newpress.Right=0;
	if(Pad.bNewpress.Shift)Pad.Newpress.Shift=0;
	if(Pad.bNewpress.Enter)Pad.Newpress.Enter=0;
	if(Pad.bNewpress.Escape)Pad.Newpress.Escape=0;
	Pad.bNewpress = Pad.Newpress;
}
void GLFWCALL KeysHandle(int key, int action)
{
	ClearKeyboard();
	if(action == GLFW_PRESS)
	{
		switch (key) {
			case 'Q':
				
				if(!Pad.tNewpress.Q)Pad.Newpress.Q=1;
				Pad.tNewpress.Q=1;
				Pad.Held.Q=1;
				break;
			case 'A':
				if(!Pad.tNewpress.A)Pad.Newpress.A=1;
				Pad.tNewpress.A=1;
				Pad.Held.A=1;
				break;
			case 'Z':
				if(!Pad.tNewpress.Z)Pad.Newpress.Z=1;
				Pad.tNewpress.Z=1;
				Pad.Held.Z=1;
				break;
			case 'W':
				if(!Pad.tNewpress.W)Pad.Newpress.W=1;
				Pad.tNewpress.W=1;
				Pad.Held.W=1;
				break;
			case 'S':
				if(!Pad.tNewpress.S)Pad.Newpress.S=1;
				Pad.tNewpress.S=1;
				Pad.Held.S=1;
				break;
			case 'X':
				if(!Pad.tNewpress.X)Pad.Newpress.X=1;
				Pad.tNewpress.X=1;
				Pad.Held.X=1;
				break;
			case 'E':
				if(!Pad.tNewpress.E)Pad.Newpress.E=1;
				Pad.tNewpress.E=1;
				Pad.Held.E=1;
				break;
			case 'D':
				if(!Pad.tNewpress.D)Pad.Newpress.D=1;
				Pad.tNewpress.D=1;
				Pad.Held.D=1;
				break;
			case 'C':
				if(!Pad.tNewpress.C)Pad.Newpress.C=1;
				Pad.tNewpress.C=1;
				Pad.Held.C=1;
				break;
			case GLFW_KEY_RIGHT:
				if(!Pad.tNewpress.Right)Pad.Newpress.Right=1;
				Pad.tNewpress.Right=1;
				Pad.Held.Right=1;
				break;
			case GLFW_KEY_LEFT:
				if(!Pad.tNewpress.Left)Pad.Newpress.Left=1;
				Pad.tNewpress.Left=1;
				Pad.Held.Left=1;
				break;
			case GLFW_KEY_UP:
				if(!Pad.tNewpress.Up)Pad.Newpress.Up=1;
				Pad.tNewpress.Up=1;
				Pad.Held.Up=1;
				break;
			case GLFW_KEY_DOWN:
				if(!Pad.tNewpress.Down)Pad.Newpress.Down=1;
				Pad.tNewpress.Down=1;
				Pad.Held.Down=1;
				break;
			case GLFW_KEY_ESC:
				if(!Pad.tNewpress.Escape)Pad.Newpress.Escape=1;
				Pad.tNewpress.Escape=1;
				Pad.Held.Escape=1;
				break;
			case GLFW_KEY_ENTER:
				if(!Pad.tNewpress.Enter)Pad.Newpress.Enter=1;
				Pad.tNewpress.Enter=1;
				Pad.Held.Enter=1;
				break;
			case GLFW_KEY_LSHIFT:
				if(!Pad.tNewpress.Shift)Pad.Newpress.Shift=1;
				Pad.tNewpress.Shift=1;
				Pad.Held.Shift=1;
				break;
			default:
				break;
		}
	}	
	else if(action == GLFW_RELEASE)
	{
		switch (key) {
			case 'Q':
				Pad.tNewpress.Q=0;
				Pad.Newpress.Q=0;
				Pad.Held.Q=0;
				break;
			case 'A':
				Pad.tNewpress.A=0;
				Pad.Newpress.A=0;
				Pad.Held.A=0;
				break;
			case 'Z':
				Pad.tNewpress.Z=0;
				Pad.Newpress.Z=0;
				Pad.Held.Z=0;
				break;
			case 'W':
				Pad.tNewpress.W=0;
				Pad.Newpress.W=0;
				Pad.Held.W=0;
				break;
			case 'S':
				Pad.tNewpress.S=0;
				Pad.Newpress.S=0;
				Pad.Held.S=0;
				break;
			case 'X':
				Pad.tNewpress.X=0;
				Pad.Newpress.X=0;
				Pad.Held.X=0;
				break;
			case 'E':
				Pad.tNewpress.E=0;
				Pad.Held.E=0;
				break;
			case 'D':
				Pad.tNewpress.D=0;
				Pad.Newpress.D=0;
				Pad.Held.D=0;
				break;
			case 'C':
				Pad.tNewpress.C=0;
				Pad.Newpress.C=0;
				Pad.Held.C=0;
				break;
			case GLFW_KEY_RIGHT:
				Pad.tNewpress.Right=0;
				Pad.Newpress.Right=0;
				Pad.Held.Right=0;
				break;
			case GLFW_KEY_LEFT:
				Pad.tNewpress.Left=0;
				Pad.Newpress.Left=0;
				Pad.Held.Left=0;
				break;
			case GLFW_KEY_UP:
				Pad.tNewpress.Up=0;
				Pad.Newpress.Up=0;
				Pad.Held.Up=0;
				break;
			case GLFW_KEY_DOWN:
				Pad.tNewpress.Down=0;
				Pad.Newpress.Down=0;
				Pad.Held.Down=0;
				break;
			case GLFW_KEY_ESC:
				Pad.tNewpress.Escape=0;
				Pad.Newpress.Escape=0;
				Pad.Held.Escape=0;
				break;
			case GLFW_KEY_ENTER:
				Pad.tNewpress.Enter=0;
				Pad.Newpress.Enter=0;
				Pad.Held.Enter=0;
				break;
			case GLFW_KEY_LSHIFT:
				Pad.tNewpress.Shift=0;
				Pad.Newpress.Shift=0;
				Pad.Held.Shift=0;
				break;
			default:
				break;
		}
	}
}

PadType GetPad()
{
	ReClearKeyboard();
	return Pad;
}

////////////////////////// 

/* Joystick Control*/

//////////////////////////

SDL_Joystick *joystick[4];

MK_Joystick::MK_Joystick(unsigned short numJoystick, unsigned short numButtons)
{
	NumJoystick = numJoystick;
	NumButtons = numButtons;
	InitJoystick(NumJoystick);
	//mButtonHeld = new unsigned short(NumButtons);
	//mButtonNewpress = new unsigned short(NumButtons);
	//bButtonNewpress = new unsigned short(NumButtons);
	int i;
	for(i=0; i<NumButtons; i++)
	{
		mButtonHeld[i] = 0;
		mButtonNewpress[i] = 0;
		bButtonNewpress[i] = 0;
	}
	
}
void MK_Joystick::Update()
{
	JoystickEvent(NumJoystick,NumButtons, mButtonHeld);
	int i;
	for(i=0; i<NumButtons; i++)
	{
		//cout <<"Button" << i << ":: "<< mButtonHeld[i] <<endl;
		if(mButtonHeld[i])
		{
			//cout<< "Held "  << i <<endl;
			if(bButtonNewpress[i]==1){
				mButtonNewpress[i] = 0;
				bButtonNewpress[i] = 1;
				//cout<< "NewpressReyected "  << i <<endl;
				//cout << "Button State : " <<  mButtonNewpress[i] << endl;
			}
			else 
			{
				mButtonNewpress[i] = 1;
				bButtonNewpress[i] = 1;
				//cout<< "NewpressDetected "  << i <<endl;
				//cout << "Button State : " <<  mButtonNewpress[i] << endl;
			}
		}
		else
		{
			bButtonNewpress[i] = 0;
			mButtonNewpress[i] = 0;
		}
	}
}
short MK_Joystick::GetAxis(unsigned short Axis)
{
	return SDL_JoystickGetAxis(joystick[NumJoystick], Axis);	
}

MK_Joystick::~MK_Joystick()
{
	delete mButtonHeld;
	delete mButtonNewpress;
	delete bButtonNewpress;
}

unsigned short MK_Joystick::ButtonHeld(unsigned short button)
{
	if(button > NumButtons || button == 0)return 0;
	else return mButtonHeld[button-1];
	//return SDL_JoystickGetButton(joystick[NumJoystick],button);
}
unsigned short MK_Joystick::ButtonNewpress(unsigned short button)
{
	if(button > NumButtons || button == 0)return 0;
	else return mButtonNewpress[button-1];
}
void MK_Joystick::Destroy()
{
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);	
	free(joystick[NumJoystick]);
}



void InitJoystick(int numJoystick)
{
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
    {
        cout << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }
	
	cout << SDL_NumJoysticks() << " joysticks were found." << endl;
    cout << "The names of the joysticks are:" << endl;
	int i;
    for( i=0; i < SDL_NumJoysticks(); i++ ) 
    {
        cout << "  " << i <<  ".- " << SDL_JoystickName(i) << endl;
    }
	
    SDL_JoystickEventState(SDL_ENABLE);
    joystick[numJoystick] = SDL_JoystickOpen(numJoystick);
	if(joystick[numJoystick]) cout << "Joystick Opened" << endl;
	else cout << "Joystick NOT Opened" << endl;
	cout << "Num of Buttons" << SDL_JoystickNumButtons(joystick[numJoystick]) <<endl;
	//return SDL_JoystickNumButtons(joystick[numJoystick]);
}

void JoystickEvent(int numJoystick,int maxButtons,unsigned short button[32])
{
	SDL_JoystickUpdate();
	/**x = SDL_JoystickGetAxis(joystick[numJoystick], 0);
	*y = -SDL_JoystickGetAxis(joystick[numJoystick], 1);
	*z = -SDL_JoystickGetAxis(joystick[numJoystick], 2);
	*w = -SDL_JoystickGetAxis(joystick[numJoystick], 3);*/
	//cout << "X axis: " << SDL_JoystickGetAxis(joystick[numJoystick], 0) << endl;
	
	int i;
	for (i=0; i<maxButtons; i++) 
	{
		button[i]=SDL_JoystickGetButton(joystick[numJoystick],i);
		//cout <<"Button" << i << ":: "<< button[i] <<endl;
	}
	//if(SDL_JoystickGetButton(joystick[numJoystick],0)==1)cout <<"Button 1 Presssed"<< endl;
	
}
	
	
