/*
 *  MK_Primitives.h
 *  OpenGLEX
 *
 *  Created by mike on 12/4/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

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
enum
{
	AxisX,
	AxisY,
	AxisZ
};


class MK_Cube
{
	public:
	GLfloat x,y,z;
	GLfloat ax,ay,az;
	MK_Cube(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat bx, GLfloat by, GLfloat bz);
	void Draw();

};

class MK_TPlane
{
	public:
	GLfloat x,y,z,widht,height;
	MK_TPlane(GLfloat CordX, GLfloat CordY, GLfloat CordZ, GLfloat Widht,GLfloat Height);
	void Draw(char Axis,GLfloat Repeat);
	
};
