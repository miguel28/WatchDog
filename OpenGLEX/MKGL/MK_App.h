/*
 *  MK_App.h
 *  OpenGLEX
 *
 *  Created by mike on 12/1/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "MK_Texture.h"
#include "MK_Primitives.h"
#include "MK_Mesh/MK_Models.h"
//#include "MK_Mesh/mesh.h"
#include "MK_Camera.h"
#include "MK_Text.h"
#include "MK_Materials.h"
#include "MK_Shader.h"
#include "MK_Input.h"

#ifdef WIN32
#include <windows.h>		// Must have for Windows platform builds
#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include <gl\glu.h>			// OpenGL Utilities
#include "gl\glut.h"			// Glut (Free-Glut on Windows)
#endif

// Mac OS X
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Just ignore sleep on Apple
#define Sleep(x)
#endif


class MK_Application
{
public:
	int Width, Height;
	int x,y;
	
	
	MK_Application(int x,int y, int Width, int Height, char *Title);
	void DisplayFunc(void (*func)(void));
	void ReshapeFunc(void (*func)(int width, int height));
	
	
	/*void NormalKeys(unsigned char key, int x, int y);
	void SpecialKeys(int key, int x, int y);
	void SpecialUpKeys(int key, int x, int y);
	*/
	
	void KeyboardFunc(void (*func)(unsigned char key, int x, int y));
	void KeyboardUpFunc(void (*func)(unsigned char key, int x, int y));
	void SpecialFunc(void (*func)(int key, int x, int y));
	void SpecialUpFunc(void (*func)(int key, int x, int y));
	void SetDefaultInput();
	void JoystickFunc(void (*func)(unsigned int buttonMask, int x, int y, int z), int pollInterval);
	
	
	void Run();


	
	
};
