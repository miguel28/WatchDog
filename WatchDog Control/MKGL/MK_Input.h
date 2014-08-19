/*
 *  MK_Input.h
 *  OpenGLEX
 *
 *  Created by mike on 2/6/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include <gl\glfw.h>				// Glut (Free-Glut on Windows)
#endif

// Mac OS X
#ifdef __APPLE__
#include <gl/glfw.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Just ignore sleep on Apple
#define Sleep(x)
#endif

#include <iostream>
#include <stdio.h>

typedef struct{
	GLboolean A,Z,X,S,Q,W,E,D,C,Shift,Enter,Up,Down,Left,Right,Escape; 
}KeysType;

typedef struct{
	KeysType Newpress,tNewpress,bNewpress,Held;
}PadType;

typedef struct{
	char RClick, LClick;
}ClickType;

typedef struct{
	GLshort x,y;
	ClickType Newpress,Held;
}MouseType;

void ClearKeyboard();
void GLFWCALL KeysHandle(int key, int action);
PadType GetPad();

void CheckKeyboardMouse();
void ReadMouse(int *x, int *y);



////////////////////////////////////////////////
///////////////Joystick Classes/////////////////
////////////////////////////////////////////////

void InitJoystick(int numJoystick);
void JoystickEvent(int numJoystick,int maxButtons,unsigned short button[32]);


class MK_Joystick
{
public:
	unsigned short NumJoystick;
	unsigned short NumButtons;
	unsigned short mButtonHeld[32];
	unsigned short mButtonNewpress[32];
	unsigned short bButtonNewpress[32];
	
	MK_Joystick(unsigned short numJoystick, unsigned short numButtons);
	~MK_Joystick();
	void Update();
	unsigned short ButtonHeld(unsigned short button);
	unsigned short ButtonNewpress(unsigned short button);
	short GetAxis(unsigned short Axis);
	void Destroy();
};



