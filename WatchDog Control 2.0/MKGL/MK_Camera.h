/*
 *  MK_Camera.h
 *  OpenGLEX
 *
 *  Created by mike on 12/23/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */


#include <math.h>

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

class MK_Camera
{
public:
	GLfloat X,Y,Z;
	GLfloat rotX,rotY,rotZ;	
	GLint Width,Height;
	GLdouble fovy;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
	
	MK_Camera(GLint winWidth,GLint winHeight, GLdouble Fovy, GLdouble ZNear, GLdouble ZFar);
	void ThirdPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle);
	void FristPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle);
	void FixedCamera();
};
