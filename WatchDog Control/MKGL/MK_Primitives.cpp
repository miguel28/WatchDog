/*
 *  MK_Primitives.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/4/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Primitives.h"

MK_Cube::MK_Cube(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat bx, GLfloat by, GLfloat bz)
{
	x=xx;
	y=yy;
	z=zz;
	ax=bx;
	ay=by;
	az=bz;
}
void MK_Cube::Draw()
{
	glBegin(GL_QUADS);
	
	glColor3f(0, 0, 0); glVertex3f(x,    y, z);
	glColor3f(0, 0, 1); glVertex3f(x,    y, z+az);
	glColor3f(0, 1, 1); glVertex3f(x, y+ay, z+az);
	glColor3f(0, 1, 0); glVertex3f(x, y+ay, z);
	
	glColor3f(1, 0, 0); glVertex3f( x+ax,    y, z);
	glColor3f(1, 0, 1); glVertex3f( x+ax,    y, z+az);
	glColor3f(1, 1, 1); glVertex3f( x+ax, y+ay, z+az);
	glColor3f(1, 1, 0); glVertex3f( x+ax, y+ay, z);
	
	glColor3f(0, 0, 0); glVertex3f( x,    y, z);
	glColor3f(0, 0, 1); glVertex3f( x,    y, z+az);
	glColor3f(1, 0, 1); glVertex3f( x+ax, y, z+az);
	glColor3f(1, 0, 0); glVertex3f( x+ax, y, z);
	
	glColor3f(0, 1, 0); glVertex3f(  x,  y+ay, z);
	glColor3f(0, 1, 1); glVertex3f(  x,  y+ay, z+az);
	glColor3f(1, 1, 1); glVertex3f(x+ax, y+ay, z+az);
	glColor3f(1, 1, 0); glVertex3f(x+ax, y+ay, z);
	
	glColor3f(0, 0, 0); glVertex3f(   x,    y, z);
	glColor3f(0, 1, 0); glVertex3f(   x, y+ay, z);
	glColor3f(1, 1, 0); glVertex3f(x+ax, y+ay, z);
	glColor3f(1, 0, 0); glVertex3f(x+ax,    y, z);
	
	glColor3f(0, 0, 1); glVertex3f(   x,    y, z+az);
	glColor3f(0, 1, 1); glVertex3f(   x, y+ay, z+az);
	glColor3f(1, 1, 1); glVertex3f(x+ax, y+ay, z+az);
	glColor3f(1, 0, 1); glVertex3f(x+ax,    y, z+az);
	
	glEnd();

}


MK_TPlane::MK_TPlane(GLfloat CordX, GLfloat CordY, GLfloat CordZ, GLfloat Widht,GLfloat Height)
{
	x=CordX;
	y=CordY;
	z=CordZ;
	widht=Widht;
	height=Height;
}

void MK_TPlane::Draw(char Axis,GLfloat Repeat)
{
	
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	switch(Axis)
	{
		case AxisX:
			
			
			glTexCoord2f(0.0f, 0.0f);
			glNormal3f(0,1,0);
			glVertex3f(x,y,z);

			glTexCoord2f(0.0f, Repeat);
			glNormal3f(0,1,0);
			glVertex3f(x,y,z+height);
			

			glTexCoord2f(Repeat, Repeat);
			glNormal3f(0,1,0);
			glVertex3f(x+widht,y,z+height);
			

			glTexCoord2f(Repeat, 0.0f);
			glVertex3f(x+widht,y,z);
			break;
		case AxisY:
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x,y,z);
			
			glTexCoord2f(0.0f, Repeat);
			glVertex3f(x,y+height,z);
			
			glTexCoord2f(Repeat, Repeat);
			glVertex3f(x+widht,y+height,z);
			
			glTexCoord2f(Repeat, 0.0f);
			glVertex3f(x+widht,y,z);
			break;
		
		case AxisZ:
			
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x,y,z);
	
			glTexCoord2f(0.0f, Repeat);
			glVertex3f(x,y,z+height);
	
			glTexCoord2f(Repeat, Repeat);
			glVertex3f(x,y+widht,z+height);
	
			glTexCoord2f(Repeat, 0.0f);
			glVertex3f(x,y+widht,z);
			break;
	}
	glEnd();
}




