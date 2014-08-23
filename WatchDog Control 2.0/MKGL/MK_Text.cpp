/*
 *  MK_Text.cpp
 *  OpenGLEX
 *
 *  Created by mike on 12/29/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include "MK_Text.h"

MK_Text::MK_Text()
{
	R=1.0f;
	G=1.0f;
	B=1.0f;
	Alpha =1.0f;
}

void MK_Text::SetColor(GLfloat r,GLfloat g,GLfloat b, GLfloat a)
{
	R=r;
	G=g;
	B=b;
	Alpha = a;
}

int MK_Text::TextLen(char *Text)
{
	int Counter = 0;
	while(Text[Counter]!='\0')Counter++; 
	return Counter;
}

void MK_Text::DrawText(char *Text,...)
{

	
	glPushAttrib(GL_ENABLE_BIT);
	
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_DEPTH_TEST);
	

	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0,800*4,600*4,0,-50,50);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

			glLoadIdentity();

			int i, len;
			len = TextLen(Text);
			glColor4f(R,G,B,Alpha);
			glRasterPos2i(X*10,(Y*10)+70);
			for(i = 0; i<len; i++)
			{
				//glRasterPos2i(X+(i*80),Y);
				//glutStrokeCharacter(GLUT_STROKE_ROMAN,Text[i]);
				//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,Text[i]);
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13,Text[i]);
			}
		
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

