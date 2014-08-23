/*
 *  MK_Materials.h
 *  OpenGLEX
 *
 *  Created by mike on 1/15/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
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
	MK_Directional,
	MK_Spot,
	MK_Spot_CutOff
};

class MK_Light
{
private:
	GLfloat Ambient[4];
	GLfloat Difuse[4];
	GLfloat Especular[4];
	GLfloat Position[4];
	GLfloat Direction[4];
	GLenum Light;
	char Type;
public:	
	GLfloat X,Y,Z,RotX,RotY,RotZ;
	MK_Light(GLenum numLight, char pType);
	void Blind();
	void SetPosition(GLfloat posx, GLfloat posy, GLfloat posz);
	void SetDirection(GLfloat dirx, GLfloat diry, GLfloat dirz);
	void SetAmbient(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void SetDifuse(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void SetEspecular(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void Traslate(GLfloat posx, GLfloat posy, GLfloat posz);
	void Rotate(GLfloat dirx, GLfloat diry, GLfloat dirz);
};

class MK_Material 
{
private:
	GLfloat Ambient[4];
	GLfloat Difuse[4];
	GLfloat Specular[4];
	GLint Shininess;
public:
	MK_Material();
	void Blind();
	void SetAmbient(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void SetDifuse(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void SetEspecular(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha);
	void SetShininess(GLint Value);
};
