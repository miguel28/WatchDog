/*
 *  MK_Materials.cpp
 *  OpenGLEX
 *
 *  Created by mike on 1/15/13.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Materials.h"

MK_Light::MK_Light(GLenum numLight, char pType)
{
	Light= numLight;
	Type = pType;
	
	X = Y = Z = RotX = RotY = RotZ = 0;
	
	Difuse[0] = 1.0f; 
	Difuse[1] = 0.0f; 
	Difuse[2] = 0.0f; 
	Difuse[3] = 1.0f;
	
	Especular[0] = 1.0f; 
	Especular[1] = 0.0f; 
	Especular[2] = 0.0f; 
	Especular[3] = 1.0f;
	
	Ambient[0] = 0.4f; 
	Ambient[1] = 0.4f; 
	Ambient[2] = 0.4f; 
	Ambient[3] = 1.0f;
	
	Position[0] =  0.0f;
	Position[1] =  0.0f;
	Position[2] =  0.0f;
	Position[3] =  1.0f;
	
	Direction[0]=1.0f;
	Direction[1]=0.0f;
	Direction[2]=0.0f;
	
	switch(Type)
	{
		case MK_Directional:
			Position[3] = 0.0f;
			break;
		case MK_Spot:
		case MK_Spot_CutOff:
			Position[3] = 1.0f;
			break;
	}
}

void MK_Light::Blind()
{
	glPushMatrix();
	{
		glLoadIdentity();
	
		glLightfv(Light, GL_AMBIENT, Ambient);
		glLightfv(Light, GL_DIFFUSE, Difuse);
		glLightfv(Light, GL_SPECULAR, Especular);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
	
		glLightf(Light, GL_LINEAR_ATTENUATION, 0.1);
	
		if(Type==MK_Spot_CutOff)glLightf(Light,GL_SPOT_CUTOFF,30.0f);
	
	
		glTranslatef(X,Y,Z);
		glRotatef(RotX, 1.0f, 0.0f, 0.0f);
		glRotatef(RotY, 0.0f, 1.0f, 0.0f);
		glRotatef(RotZ, 0.0f, 0.0f, 1.0f);
	
		glLightfv(Light, GL_POSITION, Position);
		if(Type==MK_Spot_CutOff)glLightfv(Light, GL_SPOT_DIRECTION, Direction);
	}
	glPopMatrix();
}

void MK_Light::SetPosition(GLfloat posx, GLfloat posy, GLfloat posz)
{
	Position[0] =  posx;
	Position[1] =  posy;
	Position[2] =  posz;	
}
void MK_Light::SetDirection(GLfloat dirx, GLfloat diry, GLfloat dirz)
{
	Direction[0] = dirx;
	Direction[1] = diry;
	Direction[2] = dirz;
}
void MK_Light::SetDifuse(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Difuse[0] = Red; 
	Difuse[1] = Green; 
	Difuse[2] = Blue; 
	Difuse[3] = Alpha;
}
void MK_Light::SetEspecular(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Especular[0] = Red; 
	Especular[1] = Green; 
	Especular[2] = Blue; 
	Especular[3] = Alpha;
}
void MK_Light::SetAmbient(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Ambient[0] = Red; 
	Ambient[1] = Green; 
	Ambient[2] = Blue; 
	Ambient[3] = Alpha;
}
void MK_Light::Traslate(GLfloat posx, GLfloat posy, GLfloat posz)
{
	X=posx;
	Y=posy;
	Z=posz;
}
void MK_Light::Rotate(GLfloat dirx, GLfloat diry, GLfloat dirz)
{
	RotX=dirx;
	RotY=diry;
	RotZ=dirz;
}

MK_Material::MK_Material()
{
	Difuse[0] = 0.1f; 
	Difuse[1] = 0.1f; 
	Difuse[2] = 0.1f; 
	Difuse[3] = 1.0f;
	
	Specular[0] = 1.0f; 
	Specular[1] = 0.0f; 
	Specular[2] = 0.0f; 
	Specular[3] = 1.0f;
	
	Ambient[0] = 0.0f; 
	Ambient[1] = 0.0f; 
	Ambient[2] = 0.4f; 
	Ambient[3] = 1.0f;
	
	Shininess = 255;
}
void MK_Material::Blind()
{
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS,Shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Difuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
}
void MK_Material::SetDifuse(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Difuse[0] = Red; 
	Difuse[1] = Green; 
	Difuse[2] = Blue; 
	Difuse[3] = Alpha;
}
void MK_Material::SetEspecular(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Specular[0] = Red; 
	Specular[1] = Green; 
	Specular[2] = Blue; 
	Specular[3] = Alpha;
}
void MK_Material::SetAmbient(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha)
{
	Ambient[0] = Red; 
	Ambient[1] = Green; 
	Ambient[2] = Blue; 
	Ambient[3] = Alpha;
}

void MK_Material::SetShininess(GLint Value)
{
	Shininess = Value;
}

