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
	
	Position.X = Position.Y = Position.Z = 0.0f;
	
	rotX=rotY=rotZ =0.0f;
}

void MK_Camera::FixedCamera(Vector3f lookAt)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, zNear, zFar);
	glViewport(0, 0, Width, Height);
	
	gluLookAt(Position.X, Position.Y, Position.Z, lookAt.X, lookAt.Y, lookAt.Z, 0, 1, 0);

	//glTranslatef(Position.X, Position.Y, Position.Z);
	//glRotatef(180, 0, 1, 0);
	//glRotatef(rotX, 1, 0, 0);
	//glRotatef(-rotY+180.0f, 0, 1, 0);
	//glRotatef(rotZ, 0, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
}


void MK_Camera::ThirdPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle)
{
	
	//Position.X = -(objX-(Distance*cos(Angle*M_PI/180)));
	//Position.Y = -(Distance*0.7f); 
	//Position.Z = (objY-(Distance*sin(Angle*M_PI/180)));
	
	//rotY = -Angle;
	//FixedCamera();
}

void MK_Camera::ThirdPersonCamera(Vector3f lookPosition, GLfloat Angle,GLfloat Distance)
{
	
	Position.X = (lookPosition.X - (Distance*sinf(Angle*M_PI/180)));
	Position.Y = (Distance*0.5f); 
	Position.Z = (lookPosition.Z - (Distance*cosf(Angle*M_PI/180)));
	
	//Position.X = objPosition.X;
	//Position.Y = objPosition.Y; 
	//Position.Z = objPosition.Z;
	//rotY = Angle;
	FixedCamera(lookPosition);
}

void MK_Camera::FristPersonCamera(GLfloat objX,GLfloat objY,GLfloat objZ, GLfloat Angle,GLfloat Distance, GLfloat TiltAngle)
{
	
	//Position.X = -(objX);
	//Position.Y = -Distance*0.8f; 
	//Position.Z = (objY);
	
	//rotY = -Angle;
	//FixedCamera();
}
