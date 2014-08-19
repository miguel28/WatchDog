/*
 *  MK_Input.h
 *  OpenGLEX
 *
 *  Created by mike on 2/6/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifndef MK_Input_H
#define MK_Input_H


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

#define MAX_KEYS 400

#define KEY_SPACE GLFW_KEY_SPACE
#define KEY_ESC GLFW_KEY_ESC
#define KEY_UP GLFW_KEY_UP
#define KEY_DOWN GLFW_KEY_DOWN
#define KEY_LEFT GLFW_KEY_LEFT
#define KEY_RIGHT GLFW_KEY_RIGHT

/*#ifdef WIN32
enum HATS
{
	HAT_CENTERED,
	HAT_UP,
	HAT_RIGHT,
	HAT_DOWN,
	HAT_LEFT,
	HAT_RIGHTUP,
	HAT_RIGHTDOWN,
	HAT_LEFTUP,
	HAT_LEFTDOWN
};
#else*/
enum HATS
{
	HAT_CENTERED,
	HAT_UP,
	HAT_RIGHT,
	HAT_LEFT2,
	HAT_DOWN,
	HAT_RIGHTUP,
	HAT_RIGHTDOWN,
	HAT_LEFTUP,
	HAT_LEFT
};
/*#endif*/




char GetKeyHeld(int key);
char GetKeyNewpress(int key);

void GLFWCALL KeysHandle(int key, int action);

void CheckKeyboardMouse();
void ReadMouse(int *x, int *y);



////////////////////////////////////////////////
///////////////Joystick Classes/////////////////
////////////////////////////////////////////////
void InitSDLSubsytem();
void InitJoystick(int numJoystick);
void JoystickEvent(int numJoystick,int maxButtons,unsigned short button[32]);


class MK_Joystick
{
private:
    
	unsigned short NumJoystick;
	unsigned short NumButtons;
	unsigned short mButtonHeld[32];
	unsigned short mButtonNewpress[32];
	unsigned short bButtonNewpress[32];
public:
    char hatPrevState[5];
	char hatNewpressState[5];
	MK_Joystick(unsigned short numJoystick, unsigned short numButtons);
	~MK_Joystick();
	void Update();
	unsigned short ButtonHeld(unsigned short button);
	unsigned short ButtonNewpress(unsigned short button);
	int GetAxis(unsigned short Axis);
	char GetHatHeld(int NumHat);
	char GetHatNewPress(int NumHat);
	void Destroy();
};

#endif

