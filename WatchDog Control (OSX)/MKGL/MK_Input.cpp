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

char fNewpress[MAX_KEYS] ={0x00};
char ftNewpress[MAX_KEYS] ={0x00};
char fbNewpress[MAX_KEYS] ={0x00};
char fHeld[MAX_KEYS] ={0x00};

void ClearKeyboard()
{
	int i;
	for(i=0; i<MAX_KEYS; i++)
		fNewpress[i] = 0x00;
}

void ReClearKeyboard(int key)
{
	if(fbNewpress[key])
		fNewpress[key] = 0x00;
	fbNewpress[key] = fNewpress[key];
}

char GetKeyHeld(int key)
{
	return fHeld[key];
}
char GetKeyNewpress(int key)
{
	ReClearKeyboard(key);
	return fNewpress[key];
}

void GLFWCALL KeysHandle(int key, int action)
{
	if(key>MAX_KEYS)return;
	//ClearKeyboard();
		
	if(action == GLFW_PRESS)
	{
		if(!ftNewpress[key])fNewpress[key]=0x01;
		ftNewpress[key]=0x01;
		fHeld[key]=0x01;
		
	}
	else if(action == GLFW_RELEASE)
	{
		fNewpress[key]=0x00;
		ftNewpress[key]=0x00;
		fHeld[key]=0x00;
	}
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

	int i;
	for(i=0; i<NumButtons; i++)
	{
		mButtonHeld[i] = 0;
		mButtonNewpress[i] = 0;
		bButtonNewpress[i] = 0;
	}
	for(i=0; i<5; i++)
	{
		hatPrevState[i] = 0;
        hatNewpressState[i] =0;
	}
}
void MK_Joystick::Update()
{
	JoystickEvent(NumJoystick,NumButtons, mButtonHeld);
	int i;
	for(i=0; i<NumButtons; i++)
	{
		if(mButtonHeld[i])
		{
			if(bButtonNewpress[i]==1){
				mButtonNewpress[i] = 0;
				bButtonNewpress[i] = 1;
			}
			else 
			{
				mButtonNewpress[i] = 1;
				bButtonNewpress[i] = 1;
			}
		}
		else
		{
			bButtonNewpress[i] = 0;
			mButtonNewpress[i] = 0;
		}
	}
	
	char TempHat = GetHatHeld(0);
	if(hatPrevState[0] != TempHat && TempHat!=HAT_CENTERED)
	{
		hatNewpressState[0] = TempHat;
	}
	else 
	{
	    hatNewpressState[0] = HAT_CENTERED;
	}
	hatPrevState[0] = TempHat;

	TempHat = GetHatHeld(1);
	if(hatPrevState[1] != TempHat && TempHat!=HAT_CENTERED)
	{
		hatNewpressState[1] = TempHat;
	}
	else 
	{
	    hatNewpressState[1] = HAT_CENTERED;
	}
	hatPrevState[1] = TempHat;
	
}
int MK_Joystick::GetAxis(unsigned short Axis)
{
	return SDL_JoystickGetAxis(joystick[NumJoystick], Axis);	
}

char MK_Joystick::GetHatHeld(int NumHat)
{
    return SDL_JoystickGetHat(joystick[NumJoystick], NumHat);
}

char MK_Joystick::GetHatNewPress(int NumHat)
{
	return hatNewpressState[0];
}

MK_Joystick::~MK_Joystick()
{
	Destroy();
}

unsigned short MK_Joystick::ButtonHeld(unsigned short button)
{
	if(button > NumButtons || button == 0)return 0;
	else return mButtonHeld[button-1];
}
unsigned short MK_Joystick::ButtonNewpress(unsigned short button)
{
	if(button > NumButtons || button == 0)return 0;
	else return mButtonNewpress[button-1];
}
void MK_Joystick::Destroy()
{
	//free(joystick[NumJoystick]);
}

void InitSDLSubsytem()
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
}

void InitJoystick(int numJoystick)
{
    joystick[numJoystick] = SDL_JoystickOpen(numJoystick);
	if(joystick[numJoystick])
	{
		cout << "Joystick Opened" << endl;
	
		/** Joystick Info **/
		cout << "Joystick Info : " << SDL_JoystickName(numJoystick) << endl;
		cout << "	Num of Buttons: " << SDL_JoystickNumButtons(joystick[numJoystick]) <<endl;
		cout << "	Num of Axes: " << SDL_JoystickNumAxes(joystick[numJoystick]) <<endl;
		cout << "	Num of Balls: " << SDL_JoystickNumBalls(joystick[numJoystick]) <<endl;
		cout << "	Num of Hats: " << SDL_JoystickNumHats(joystick[numJoystick]) <<endl;
	}
	else cout << "Joystick NOT Opened" << endl;
}

void JoystickEvent(int numJoystick,int maxButtons,unsigned short button[32])
{
	SDL_JoystickUpdate();
	
	int i;
	for (i=0; i<maxButtons; i++) 
	{
		button[i]=SDL_JoystickGetButton(joystick[numJoystick],i);
	}
}
	
	
