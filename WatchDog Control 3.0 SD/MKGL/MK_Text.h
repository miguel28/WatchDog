/*
 *  MK_Text.h
 *  OpenGLEX
 *
 *  Created by mike on 12/29/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */
#include <string>

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


class MK_Text
{
public:
	GLint X,Y;
	GLfloat R,G,B,Alpha;
	MK_Text();
	~MK_Text();
	void DrawText(char *Text,...);
	void SetColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a);
protected:
	int TextLen(char *Text);
};

