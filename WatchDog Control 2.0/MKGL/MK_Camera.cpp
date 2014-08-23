/*
 *  MK_Camera.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/23/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Camera.h"

MK_Camera::MK_Camera(GLint winWidth,GLint winHeight, GLdouble Fovy, GLdouble ZNear, GLdouble ZFar)	
{
	Width = winWidth;
	Height = winHeight;
	aspect = Width/(float)Height;
	fovy = Fovy;
	zNear = ZNear;
	zFar = ZFar;
}

void MK_Camera::FixedCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, zNear, zFar);
	glViewport(0, 0, Width, Height);

	glRotatef(90, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	glTranslatef(X, Y, Z);
	
	glMatrixMode(GL_MODELVIEW);
}


void MK_Camera::ThirdPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle)
{
	
	X = -(objX-(Distance*cos(Angle*M_PI/180)));
	Y = -((Distance*0.7f*cos(TiltAngle*M_PI/180))); 
	Z = (objY-(Distance*sin(Angle*M_PI/180)));
	
	rotY = -Angle;
	//rotZ = TiltAngle;
	//rotX=30;
	FixedCamera();
}

void MK_Camera::FristPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle)
{
	
	X = -(objX);
	Y = -Distance*0.8f; 
	Z = (objY);
	
	rotY = -Angle;
	//rotZ = TiltAngle;
	FixedCamera();
}
